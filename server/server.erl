-module(server).
-import(files, [readAccounts/0, writeAccounts/1]).
-import(accounts, [createAccount/4, removeAccount/4, login/4, logout/4, auth/3]).
-export([start/1, start/0, ca/2, ra/2, li/2, lo/2, jo/2, on/0, parseGame/2]).

start(Port) -> register(?MODULE, spawn(fun()-> server(Port) end)).
start() -> register(?MODULE, spawn(fun()-> server(8000) end)).

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
        {gameover, Winner} ->
            io:format("Game Over. Winner: ~p ~n", [Winner]),
            Res = maps:get(Winner, Users),
            case Res of
                {badkey, _} -> serverLoop(Users, Party, Ongoing - 1);
                {badmap, _} -> serverLoop(Users, Party, Ongoing - 1);
                {Password, Score, LoggedIn} ->
                    NewUsers = maps:update(Winner, {Password, Score + 1, LoggedIn}, Users),
                    files:writeAccounts(NewUsers),
                    serverLoop(NewUsers, Party, Ongoing - 1)
            end
    end.

% Queue -> List of players in party queue : [{user, pid}, ...]
party(Queue) ->
    Limit = 2,
    io:fwrite("Party users: "),
    [io:format("~p ", [User]) || {User, _Pid} <- Queue],
    io:fwrite("\n"),
    receive
        timeout ->
            game(Queue);
        {join, User, From} ->
            From ! {done, self()},
            NewQueue = Queue ++ [{User, From}],
            case length(NewQueue) of
                8 ->
                    game(NewQueue);
                Limit -> % TODO -> 3 jogadores
                    Self = self(),
                    spawn(fun() -> receive after 10000 -> Self ! timeout end end), % TODO -> 30seg
                    party(NewQueue);
                _ ->
                    party(NewQueue)
            end;
        {leave, U, From} ->
            From ! leave_done,
            NewQueue = [{User, Pid} || {User, Pid} <- Queue, User /= U],
            L = length(NewQueue),
            if
                L == Limit - 1 -> receive timeout -> party(NewQueue) end;
                true -> party(NewQueue)
            end
    end.

game(Players) ->
    io:fwrite("Starting game.\n"),
    ?MODULE ! {start, self()},
    [From ! {start, self()}|| {_User, From} <- Players],
    NewPlayers = initGame(Players, []),
    gameTimer(NewPlayers).

initGame([], _UsedPositions) -> #{};
initGame([{Player, From}| Players], UsedPositions) ->
    case rand:uniform(3) of
        1 -> Color = red;
        2 -> Color = green;
        3 -> Color = blue
    end,
    X = float(rand:uniform(20)),
    Y = float(rand:uniform(20)),
    case lists:member({X, Y}, UsedPositions) of
        false ->
            Pos = {X, Y},
            PlayerMap = initGame(Players, [Pos | UsedPositions]),
            maps:put(Player, {From, Color, Pos, 1, 2}, PlayerMap);
        true ->
            initGame([{Player, From} | Players], UsedPositions)
    end.

gameTimer(Players) ->
    Self = self(),
    spawn(fun() -> receive after 100 -> Self ! timeout end end),
    NewPlayers = Players, % TODO -> handleGame(Players),
    Info = parseGame(maps:to_list(NewPlayers), []),
    [io:format("~p ~f ~f~n", [Player, X, Y]) || {Player, {_From, _Color, {X, Y}, _Mass, _Speed}} <- maps:to_list(Players)],
    [From ! Info || {_Player, {From, _Color, _Pos, _Mass, _Speed}} <- maps:to_list(Players)],
    gameLoop(Players).

gameLoop(Players) ->
    receive
        timeout ->
            gameTimer(Players);
        {leave, Username, From} ->
            handleRemovePlayer(Players, Username),
            From ! leave_done;
        {Info, _From} ->
            NewPlayers = handle(Players, Info),
            gameLoop(NewPlayers)
    end.

% TODO -> From ! defeat antes de chamar esta funçao com colisoes
handleRemovePlayer(Players, Username) ->
    NewPlayers = maps:remove(Username, Players),
    case maps:to_list(NewPlayers) of
        [{LastPlayer, {From, _Color, {_X, _Y}, _Mass, _Speed}}] ->
            ?MODULE ! {gameover, LastPlayer},
            From ! winner;
        _ -> gameLoop(NewPlayers)
    end.

normalize(X, Y) ->
    Sqrt = math:sqrt(X*X + Y*Y),
    case Sqrt of
        0.0 -> {X, Y};
        _ -> {X / Sqrt, Y / Sqrt}
    end.

handle(Players, {Username, MouseX, MouseY}) -> 
    Res = maps:get(Username, Players),
    case Res of
        {badmap, _} -> Players;
        {badkey, _} -> Players;
        {From, Color, {OldX, OldY}, Mass, Speed} ->
            {DirX, DirY} = normalize(MouseX, MouseY),
            {X, Y} = {OldX + DirX * Speed, OldY + DirY * Speed},
            maps:update(Username, {From, Color, {X, Y}, Mass, Speed}, Players)
    end.

% TODO falta calcular colisoes e etc.
handleGame(_Players) -> undefined.

parseGame([], List) -> string:concat(string:join(List, "|"), "\n");
parseGame([{Player, {_From, Color, {X, Y}, Mass, Speed}} | Tail], List) ->
    InfoPlayer = string:join([Player, atom_to_list(Color), float_to_list(X), float_to_list(Y), integer_to_list(Mass), integer_to_list(Speed)], " "),
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
            end;
        ["join", Info] ->
            [Username, Password] = string:split(Info, " "),
            ?MODULE ! {join, Username, Password, self()},
            receive
                {done, Party} ->
                    gen_tcp:send(Sock, "done\n"),
                    clientGame(Sock, Party, Username);
                full_server -> gen_tcp:send(Sock, "full_server\n");
                invalid_auth -> gen_tcp:send(Sock, "invalid_auth\n")
            end;
        _ -> io:fwrite("Incorrect syntax in tcp request.\n")
    end.

clientGame(Sock, Party, Username) ->
    receive
        leave_done -> 
            gen_tcp:send(Sock, "done\n"),
            client(Sock);
        {tcp, _, Data} ->
            [DataString, _] = string:split(binary_to_list(Data), "#"),
            io:format("-> ~p~n", [DataString]),
            case DataString of
                "leave" -> Party ! {leave, Username, self()};
                _ -> io:fwrite("Failed to leave game.\n")
            end,
            clientGame(Sock, Party, Username);
        {tcp_closed, _} ->
            Party ! {leave, Username, self()};
        {tcp_error, _} ->
            Party ! {leave, Username, self()};
        {start, _From} ->
            gen_tcp:send(Sock, "start\n"),
            clientGameLoop(Sock, Party, Username);
        _ ->
            clientGame(Sock, Party, Username)
    end.

clientGameLoop(Sock, Party, Username) ->
    receive
        leave_done -> 
            gen_tcp:send(Sock, "done\n"),
            client(Sock);
        winner ->
            gen_tcp:send(Sock, "winner\n"),
            client(Sock);
        defeat ->
            gen_tcp:send(Sock, "defeat\n"),
            client(Sock);
        {tcp, _, Data} ->
            DataString = string:trim(binary_to_list(Data), trailing, "\n"),
            case string:split(DataString, "#") of
                ["mouse", Info] ->
                    [X, Y] = string:split(Info, " "),
                    Party ! {{Username, list_to_float(X), list_to_float(Y)}, self()};
                ["leave", _] -> Party ! {leave, Username, self()}
            end,
            clientGameLoop(Sock, Party, Username);
        {tcp_closed, _} -> Party ! {leave, Username, self()};
        {tcp_error, _} -> Party ! {leave, Username, self()};
        Info ->
            gen_tcp:send(Sock, Info)
    end,
    clientGameLoop(Sock, Party, Username).