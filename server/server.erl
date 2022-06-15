-module(server).
-import(files, [readAccounts/0, writeAccounts/1]).
-import(accounts, [createAccount/4, removeAccount/4, login/4, logout/4, auth/3]).
-export([start/1, ca/2, ra/2, li/2, lo/2, jo/2, on/0]).

start(Port) -> register(?MODULE, spawn(fun()-> server(Port) end)).

% -----------------------------------
% Server starts here
% -----------------------------------

server(Port) ->
    ResTCP = gen_tcp:listen(Port, [binary, {packet, line}, {reuseaddr, true}]),
    case ResTCP of
        {error, Reason} -> io:fwrite("Error - Can't create tcp socket\n"), Reason;
        {ok, LSock} ->
            spawn(fun() -> acceptor(LSock) end),
            Party = spawn(fun() -> party([]) end),
            serverLoop(files:readAccounts(), Party, 0)
    end.

% Users -> Map of users : username -> {password, score, loggedIn}
% Party -> Pid of current party
% Ongoing -> Number of ongoing games
serverLoop(Users, Party, Ongoing) ->
    receive
        {create_account, User, Password, From} ->
            NewUsers = accounts:createAccount(Users, User, Password, From),
            serverLoop(NewUsers, Party, Ongoing);
        {remove_account, User, Password, From} ->
            NewUsers = accounts:removeAccount(Users, User, Password, From),
            serverLoop(NewUsers, Party, Ongoing);
        {login, User, Password, From} ->
            NewUsers = accounts:login(Users, User, Password, From),
            serverLoop(NewUsers, Party, Ongoing);
        {logout, User, Password, From} ->
            NewUsers = accounts:logout(Users, User, Password, From),
            serverLoop(NewUsers, Party, Ongoing);
        {join, User, Password, From} ->
            Auth = accounts:auth(Users, User, Password),
            if
                Ongoing == 4 ->
                    From ! full_server;
                Auth ->
                    Party ! {join, User, From};
                true ->
                    From ! invalid_auth
            end,
            serverLoop(Users, Party, Ongoing);
        {start, _From} ->
            NewParty = spawn(fun() -> party([]) end),
            serverLoop(Users, NewParty, Ongoing + 1);
        {online, From} ->
            From ! [Username || {Username, {_Password, _Score, LoggedIn}} <- maps:to_list(Users), LoggedIn],
            serverLoop(Users, Party, Ongoing);
        {leaderboard, From} ->
            From ! [{Username, Score} || {Username, {_Password, Score, _LoggedIn}} <- maps:to_list(Users)],
            serverLoop(Users, Party, Ongoing);
        {gameover} ->
            gameover_undefined
    end.

% Queue -> List of players in party queue : [{user, pid}, ...]
party(Queue) ->
    io:fwrite("Party users: "),
    [io:format("~p ", [User]) || {User, Pid} <- Queue],
    io:fwrite("\n"),
    receive
        timeout ->
            game(Queue);
        {join, User, From} ->
            From ! {ok, self()},
            NewQueue = Queue ++ [{User, From}],
            case length(NewQueue) of
                8 ->
                    game(NewQueue);
                3 ->
                    Self = self(),
                    spawn(fun() -> receive after 30000 -> Self ! timeout end end),
                    party(NewQueue);
                _ ->
                    party(NewQueue)
            end;
        {leave, U, From} ->
            From ! ok,
            party([{User, Pid} || {User, Pid} <- Queue, User /= U])
    end.

game(Players) ->
    io:fwrite("Starting game.\n"),
    ?MODULE ! {start, self()},
    NewPlayers = initGame(Players, []),
    gameTimer(NewPlayers).

initGame([], UsedPositions) -> #{};
initGame([{Player, From}| Players], UsedPositions) ->
    case rand:uniform(3) of
        1 -> Color = red;
        2 -> Color = green;
        3 -> Color = blue
    end,
    X = rand:uniform(20),
    Y = rand:uniform(20),
    case lists:member({X, Y}, UsedPositions) of
        false ->
            Pos = {X, Y},
            PlayerMap = initGame(Players, [Pos | UsedPositions]),
            maps:put(Player, {From, Color, Pos, 1, 1}, PlayerMap);
        true ->
            initGame([{Player, From} | Players], UsedPositions)
    end.

gameTimer(Players) ->
    Self = self(),
    spawn(fun() -> receive after 100 -> Self ! timeout end end),
    NewPlayers = handleGame(Players),
    Info = parseGame(maps:to_list(NewPlayers), []),
    [From ! Info || {_Player, {From, _Color, _Pos, _Mass, _Speed}} <- maps:to_list(Players)],
    gameLoop(Players).

gameLoop(Players) ->
    receive
        timeout ->
            gameTimer(Players);
        {Info, From} ->
            NewPlayers = handle(Players, Info),
            gameLoop(NewPlayers)
    end.

% errado -> altera posiçao em vez de calcular direçao/nova posiçao
handle(Players, {Username, X, Y}) -> 
    Res = maps:get(Username, Players),
    case Res of
        {badmap, _} -> Players;
        {badkey, _} -> Players;
        {_Username, {From, Color, _X, _Y, Mass, Speed}} -> maps:update(Player, {From, Color, X, Y, Mass, Speed}, Players)
    end.

% falta calcular colisoes e etc.
handleGame(Players) -> undefined.

parseGame([], List) -> string:join(List, "|");
parseGame([{Player, {From, Color, {X, Y}, Mass, Speed}} | Tail], List) ->
    InfoPlayer = string:join([Player, atom_to_list(Color), integer_to_list(X), integer_to_list(Y), integer_to_list(Mass), integer_to_list(Speed)], " "),
    parseGame(Tail, [InfoPlayer | List]).

% -----------------------------------
% Test functions for server
% -----------------------------------

ca(A, B) -> ?MODULE ! {create_account, A, B, self()}, receive Res -> Res end.
ra(A, B) -> ?MODULE ! {remove_account, A, B, self()}, receive Res -> Res end.
li(A, B) -> ?MODULE ! {login, A, B, self()},          receive Res -> Res end.
lo(A, B) -> ?MODULE ! {logout, A, B, self()},         receive Res -> Res end.
jo(A, B) -> ?MODULE ! {join, A, B, self()},           receive Res -> Res end.
on(    ) -> ?MODULE ! {online, self()},               receive Map -> Map end.

% -----------------------------------
% Acceptor and client start here
% -----------------------------------

acceptor(LSock) ->
    ResTCP = gen_tcp:accept(LSock),
    spawn(fun() -> acceptor(LSock) end),
    case ResTCP of
        {error, Reason} -> io:fwrite("Error - Can't connect to tcp.\n"), Reason;
        {ok, Sock} -> client(Sock)
    end.

client(Sock) ->
    receive
        {tcp, _, Data} ->
            String = binary_to_list(string:trim(Data, trailing, "\n")),
            handleClientInput(String, Sock),
            client(Sock)
    end.

handleClientInput(String, Sock) ->
    case string:split(String, "#") of
        ["create_account", Info] ->
            [Username, Password] = string:split(Info, " "),
            ?MODULE ! {create_account, Username, Password, self()},
            receive
                done -> gen_tcp:send(Sock, "done\n");
                user_exists -> gen_tcp:send(Sock, "user_exists\n");
                invalid_password -> gen_tcp:send(Sock, "invalid_password\n")
            end;
        ["remove_account", Info] ->
            [Username, Password] = string:split(Info, " "),
            ?MODULE ! {remove_account, Username, Password, self()},
            receive
                done -> gen_tcp:send(Sock, "done\n");
                invalid_account -> gen_tcp:send(Sock, "invalid_account\n");
                invalid_password -> gen_tcp:send(Sock, "invalid_password\n")
            end;
        ["logout", Info] ->
            [Username, Password] = string:split(Info, " "),
            ?MODULE ! {logout, Username, Password, self()},
            receive
                done -> gen_tcp:send(Sock, "done\n");
                invalid_account -> gen_tcp:send(Sock, "invalid_account\n");
                invalid_password -> gen_tcp:send(Sock, "invalid_password\n")
            end;
        ["login", Info] ->
            [Username, Password] = string:split(Info, " "),
            ?MODULE ! {login, Username, Password, self()},
            receive
                done -> gen_tcp:send(Sock, "done\n");
                invalid_account -> gen_tcp:send(Sock, "invalid_account\n");
                invalid_password -> gen_tcp:send(Sock, "invalid_password\n")
            end;
        ["leaderboard", _] ->
            ?MODULE ! {leaderboard, self()},
            receive
                Users -> 
                    UserList = [string:join([Username, integer_to_list(Score)], " ") || {Username, Score} <- Users],
                    Res = string:join(UserList, "|"),
                    io:format("~p~n", [Res]),
                    gen_tcp:send(Sock, string:join([Res, "\n"], ""))
            end;
        ["online", _] ->
            ?MODULE ! {online, self()},
            receive
                Users ->
                    Res = string:join(Users, " "),
                    io:format("~p~n", [Res]),
                    gen_tcp:send(Sock, string:join([Res, "\n"], ""))
            end
    end.