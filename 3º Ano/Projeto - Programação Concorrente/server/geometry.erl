-module(geometry).
-export([dist/2, insideCircle/2, crystalInsideCircle/2]).

dist({X1, Y1}, {X2, Y2}) -> math:sqrt(((X2-X1)*(X2-X1)) + ((Y2-Y1)*(Y2-Y1))).

circlePoints({X, Y}, Radius) ->
    S = 0.7071 * Radius,
    [{X - Radius, Y},
    {X + Radius, Y},
    {X, Y - Radius},
    {X, Y + Radius},
    {X + S, Y + S},
    {X - S, Y - S},
    {X + S, Y - S},
    {X - S, Y + S}].

insideCircle({{X1, Y1}, Radius1}, {{X2, Y2}, Radius2}) ->
    Points1 = circlePoints({X1, Y1}, Radius1),
    Points2 = circlePoints({X2, Y2}, Radius2),
    (anyInside({{X1, Y1}, Radius1}, Points2) or anyInside({{X2, Y2}, Radius2}, Points1)).

anyInside(_, []) -> false;
anyInside({{X1,Y1},Radius},[{X2, Y2}|T]) ->
    D = dist({X1, Y1}, {X2, Y2}),
    if
        D =< Radius -> true;
        true -> anyInside({{X1,Y1},Radius}, T)
    end.

crystalPoints({{X, Y}, Radius}) ->
    [{X + Radius, Y},
    {X - Radius, Y},
    {X, Y - Radius},
    {X, Y + Radius}].

crystalInsideCircle(Crystal, Circle) ->
    Points = crystalPoints(Crystal),
    anyInside(Circle, Points).