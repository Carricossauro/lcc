-module(server).
-import(files, [readAccounts/0, writeAccounts/1]).
-export([start/1, ca/2, auth/3]).

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
            serverLoop(files:readAccounts())
    end.

serverLoop(Users) ->
    receive
        {createAccount, User, Password, From} ->
            NewUsers = createAccount(Users, User, Password, From),
            serverLoop(NewUsers)
    end.

createAccount(Users, User, Password, From) ->
    case maps:is_key(User, Users) of
        true->
            NewUsers = Users,
            From ! user_exists;
        false ->
            if
                Password == "" -> 
                    NewUsers = Users,
                    From ! invalid_password;
                true ->
                    NewUsers = maps:put(User, {Password, 0}, Users),
                    io:format("Created an account with username ~p.~n", [User]),
                    files:writeAccounts(NewUsers),
                    From ! done
            end
    end,
    NewUsers.

auth(Users, U, P) ->
    {Password, _Map} = maps:find(U, Users),
    case Password of
       badkey -> false;
       badmap -> false;
       _Password -> Password == P
    end.

ca(A, B) -> ?MODULE ! {createAccount, A, B, self()}, receive done -> ok end.

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