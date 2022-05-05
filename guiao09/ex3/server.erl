-module(server).
-export([start/1, stop/1]).

start(Port) -> spawn(fun() -> server(Port) end).
stop(Server) -> Server ! stop.

server(Port) ->
    {ok, LSock} = gen_tcp:listen(Port, [binary, {packet, line}, {reuseaddr, true}]),
    Rooms = spawn(fun()->rooms(#{}) end),
    spawn(fun() -> acceptor(LSock, Rooms) end),
    receive
        stop -> ok
    end.

acceptor(LSock, Rooms) ->
    {ok, Sock} = gen_tcp:accept(LSock),
    spawn(fun() -> acceptor(LSock, Rooms) end),
    Rooms ! {login, self()},
    user(Sock, Rooms, "main", "Anonymous").

rooms(Pids) ->
    receive
        {login, Pid} ->
            NewPids = maps:put(Pid, {"Anonymous", "main"}, Pids),
            io:format("User entered main~n", []), 
            rooms(NewPids);
        {join, Room, Pid} ->
            {User, CurrentRoom} = maps:get(Pid, Pids),
            io:format("~p entered ~p (left ~p)~n", [User, Room, CurrentRoom]),
            NewPids = maps:put(Pid, {User, Room}, Pids),
            rooms(NewPids);
        {changeUsername, Name, Pid} ->
            {User, CurrentRoom} = maps:get(Pid, Pids),
            if
                Name == "Anonymous" ->
                    handleError("Name Anonymous cannot be used.", Pid),
                    rooms(Pids);
                true ->
                    case lists:member(Name, [UUser || {_, {UUser, _}} <- maps:to_list(Pids)]) of
                        true ->
                            handleError("User " ++ Name ++ " already exists", Pid),
                            rooms(Pids);
                        false ->
                            io:format("~p changed username to ~p~n", [User, Name]),
                            NewPids = maps:put(Pid, {Name, CurrentRoom}, Pids),
                            rooms(NewPids)
                    end
            end;
        {message, Data, Pid} ->
            {User, Room} = maps:get(Pid, Pids),
            [UPid ! {broadcast, User ++ " > " ++ Data} || {UPid, {UUser, URoom}} <- maps:to_list(Pids), (URoom == Room) and (User /= UUser)],
            rooms(Pids);
        {logout, Pid} ->
            {User, Room} = maps:get(Pid, Pids),
            io:format("~p left (~p)~n", [User, Room]),
            NewPids = maps:remove(Pid, Pids),
            rooms(NewPids)
    end.

handleError(Error, Pid) ->
    io:format("Error: ~p~n", [Error]),
    Pid ! {broadcast, "Error: " ++ Error ++ "\n"}.

user(Sock, Rooms, CurrentRoom, User) ->
    receive
        {broadcast, Data} ->
            gen_tcp:send(Sock, Data),
            user(Sock, Rooms, CurrentRoom, User);
        {tcp, _, Data} ->
            case re:split(Data, " ", [{parts, 2}]) of
                [<<"join">>, Name] ->
                    RealName = string:trim(binary_to_list(Name), trailing),
                    Rooms ! {join, RealName, self()},
                    user(Sock, Rooms, Name, User);
                [<<"changeUser">>, Name] ->
                    RealName = string:trim(binary_to_list(Name), trailing),
                    Rooms ! {changeUsername, RealName, self()},
                    user(Sock, Rooms, CurrentRoom, Name);
                [<<"msg">>, Content] ->
                    RealContent = binary_to_list(Content),
                    Rooms ! {message, RealContent, self()},
                    user(Sock, Rooms, CurrentRoom, User);
                _ ->
                    gen_tcp:send(Sock, "Error: Incorrect syntax\n"),
                    user(Sock, Rooms, CurrentRoom, User)
            end;
        {tcp_closed, _} ->
            Rooms ! {logout, self()};
        {tcp_error, _, _} ->
            Rooms ! {logout, self()};
        _ ->
            io:fwrite("ERROR\n")
    end.