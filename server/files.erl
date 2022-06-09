-module(files).
-export([readAccounts/0, parseList/2, writeAccounts/1, parse/1, parseUser/1]).

readAccounts() ->
    ResFile = file:read_file("users.txt"),
    case ResFile of
        {error, _Reason} ->
            {ok, NewFile} = file:open("users.txt", [write]),
            file:close(NewFile),
            #{};
        {ok, File} ->
            FileList = string:split(File, "\n"),
            case FileList of
                [<<>>] -> #{};
                _FileList -> parseList(FileList, #{})
            end
    end.

parseList([], Users) -> Users;
parseList([H|T], Users) ->
    [User, UserInfo] = string:split(H, "."),
    [Password, Score] = string:split(UserInfo, "."),
    NewUsers = maps:put(binary_to_list(User), {binary_to_list(Password), binary_to_integer(Score), false}, Users),
    if
        T == [] -> NewUsers;
        true -> parseList(string:split(T, "\n"), NewUsers)
    end.

writeAccounts(Users) -> file:write_file("users.txt", parse(maps:to_list(Users))).

parseUser({User, {Password, Score, _LoggedIn}}) ->
    string:join([User, Password, integer_to_list(Score)], ".").

parse(L) ->
    case L of
        [] -> "";
        [H] -> parseUser(H);
        [H | T] -> string:join([parseUser(H), parse(T)], "\n")
    end.