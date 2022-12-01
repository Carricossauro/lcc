-module(accounts).
-export([createAccount/4, removeAccount/4, login/4, logout/4, auth/3]).

createAccount(Users, User, Password, From) ->
    case maps:is_key(User, Users) of
        true->
            NewUsers = Users,
            io:format("Error - User ~p already exists.~n", [User]),
            From ! user_exists;
        false ->
            if
                Password == "" -> 
                    NewUsers = Users,
                    io:format("Error - Cannot create user with empty password.~n"),
                    From ! invalid_password;
                true ->
                    NewUsers = maps:put(User, {Password, 0, false}, Users),
                    io:format("Created an account with username ~p.~n", [User]),
                    files:writeAccounts(NewUsers),
                    From ! done
            end
    end,
    NewUsers.

removeAccount(Users, User, Password, From) ->
    case maps:find(User, Users) of
        {ok, {Pass, _Score, _LoggedIn}} ->
            if
                Pass == Password ->
                    NewUsers = maps:remove(User, Users),
                    io:format("Removed the account with username ~p.~n", [User]),
                    files:writeAccounts(NewUsers),
                    From ! done;
                true ->
                    NewUsers = Users,
                    io:format("Error - Incorrect password for user ~p.~n", [User]),
                    From ! invalid_password
            end;
        _ ->
            io:format("Error - Cannot remove user ~p~n.", [User]),
            NewUsers = Users,
            From ! invalid_account
    end,
    NewUsers.

login(Users, U, P, From) ->
    case maps:find(U, Users) of
       {ok, {Password, Score, _LoggedIn}} ->
            if
                Password == P ->
                    From ! done,
                    maps:update(U, {Password, Score, true}, Users);
                true ->
                    From ! invalid_password,
                    Users
            end;
        _ ->
           From ! invalid_account,
           Users
    end.

logout(Users, U, P, From) ->
    case maps:find(U, Users) of
        {ok, {Password, Score, _LoggedIn}} ->
            if
                Password == P ->
                    From ! done,
                    maps:update(U, {Password, Score, false}, Users);
                true ->
                    From ! invalid_password,
                    Users
            end;
        _ ->
            From ! invalid_account,
            Users
    end.

auth(Users, U, P) ->
    case maps:find(U, Users) of
        {ok, {Password, _Score, LoggedIn}} ->
            (Password == P) and LoggedIn;
        _ -> false
    end.