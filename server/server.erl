-module(server).
-import(files, [readAccounts/0, writeAccounts/1]).
-export([start/1, f/2]).

start(Port) -> register(?MODULE, spawn(fun()-> server(Port) end)).

% -----------------------------------
% Server starts here
% -----------------------------------
server(Port) ->
    ResTCP = gen_tcp:listen(Port, [binary, {packet, line}, {reuseaddr, true}]),
    case ResTCP of
        {error, _Reason} -> io:fwrite("Error - Can't create tcp socket\n");
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
    {{Password, _Score}, _Map} = maps:get(U, Users),
    case Password of
        badkey -> false;
        badmap -> false;
        _Password -> Password == P
    end.

f(A, B) -> ?MODULE ! {createAccount, A, B, self()}.

% -----------------------------------
% Acceptor and client start here
% -----------------------------------

acceptor(LSock) ->
    ResTCP = gen_tcp:accept(LSock),
    spawn(fun() -> acceptor(LSock) end),
    case ResTCP of
        {error, _Reason} -> ResTCP;
        {ok, Sock} -> client(Sock)
    end.

client(Sock) -> ok.