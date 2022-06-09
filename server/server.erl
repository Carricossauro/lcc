-module(server).
-import(files, [readAccounts/0, writeAccounts/1]).
-import(accounts, [createAccount/4, removeAccount/4, login/4, logout/4, auth/3]).
-export([start/1, ca/2, ra/2, li/2, lo/2, jo/2]).

start(Port) -> register(?MODULE, spawn(fun()-> server(Port) end)).

% -----------------------------------
% Server starts here
% -----------------------------------

server(Port) ->
    ResTCP = gen_tcp:listen(Port, [binary, {packet, line}, {reuseaddr, true}]),
    case ResTCP of
        {error, Reason} -> io:fwrite("Error - Can't create tcp socket\n"), Reason;
        {ok, _LSock} ->
            %spawn(fun() -> acceptor(LSock) end),
            Party = spawn(fun() -> party([]) end),
            serverLoop(files:readAccounts(), Party, 0)
    end.

% Users -> Map of users : username -> {password, score, loggedIn}
% Party -> Pid of current party
% Ongoing -> Number of ongoing games
serverLoop(Users, Party, Ongoing) ->
    receive
        {createAccount, User, Password, From} ->
            NewUsers = accounts:createAccount(Users, User, Password, From),
            serverLoop(NewUsers, Party, Ongoing);
        {removeAccount, User, Password, From} ->
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
            party([{Pid, User} || {Pid, User} <- Queue, User /= U])
    end.

game(_Players) -> io:fwrite("Starting game.\n").

% -----------------------------------
% Test functions for server
% -----------------------------------

ca(A, B) -> ?MODULE ! {createAccount, A, B, self()}, receive Res -> Res end.
ra(A, B) -> ?MODULE ! {removeAccount, A, B, self()}, receive Res -> Res end.
li(A, B) -> ?MODULE ! {login, A, B, self()}, receive Res -> Res end.
lo(A, B) -> ?MODULE ! {logout, A, B, self()}, receive Res -> Res end.
jo(A, B) -> ?MODULE ! {join, A, B, self()}.

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

client(_Sock) -> client_undefined.