type MSet a = [(a,Int)]
data RTree a = R a [RTree a]

tree :: RTree Int
tree = R 15 [R 3 [R 4 [],R 5 [],R 6 []],R 8 [R 1 [],R 2 []]]

ex :: MSet Char
ex = [('a',9),('b',7),('c',5),('d',4),('e',2)]

addNcopies :: Eq a => MSet a -> a -> Int -> MSet a
addNcopies [] x y = [(x,y)]
addNcopies ((x,y):t) a b | x == a = insere (x,y+b) t
						   | otherwise = insere (x,y) (addNcopies t a b)

insere :: Eq a => (a,Int) -> MSet a -> MSet a
insere (x,y) [] = [(x,y)]
insere (x,y) ((a,b):t) | y <= b = (a,b):insere (x,y) t
				       | otherwise = (x,y):(a,b):t

moda :: MSet a -> [a]
moda [] = []
moda [(x,y)] = replicate y x
moda ((x,y):(a,b):t) | y >= b = moda ((x,y):t)
				     | otherwise = moda ((a,b):t)


data SReais = AA Double Double | FF Double Double
			| AF Double Double | FA Double Double
			| Uniao SReais SReais

instance Show SReais where
	show (Uniao x y) = '(':show x ++ " U " ++ show y ++ ")"
	show (AA x y) = ']':show x ++ ',':show y ++ "["
	show (FF x y) = '[':show x ++ ',':show y ++ "]"
	show (FA x y) = '[':show x ++ ',':show y ++ "["
	show (AF x y) = ']':show x ++ ',':show y ++ "]"

pertence :: Double -> SReais -> Bool
pertence x (AA a b) = x > a && x < b
pertence x (FF a b) = x >= a && x >= b
pertence x (AF a b) = x > a && x <= b
pertence x (FA a b) = x >= a && x < b
pertence x (Uniao a b) = pertence x a && pertence x b

tira :: Double -> SReais -> SReais
tira x (Uniao a b) = Uniao (tira x a) (tira x b)
tira x real@(AA a b) | pertence x real = Uniao (AA a x) (AA x b)
				     | otherwise = real
tira x real@(FF a b) | pertence x real = Uniao (FA a x) (AF x b)
					 | otherwise = real
tira x real@(AF a b) | pertence x real = Uniao (AA a x) (AF x b)
					 | otherwise = real
tira x real@(FA a b) | pertence x real = Uniao (FA a x) (AA x b)
					 | otherwise = real



percorre :: [Int] -> RTree a -> Maybe [a]
percorre [] (R a _) = Just [a]
percorre (h:t) (R a []) = Just [a]
percorre (h:t) (R a l) = Just (a:b)
					where
				 		b = aux (percorre t (l!!(h-1)))
				 		aux Nothing = []
						aux (Just p) = p
