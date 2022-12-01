

type MSet a = [(a,Int)]

cardMSet :: MSet a -> Int
cardMSet [] = 0
cardMSet [(_,x)] = x
cardMSet ((_,x):t) = x + cardMSet t