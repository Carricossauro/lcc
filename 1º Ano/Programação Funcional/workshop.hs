nub' :: Eq a => [a] -> [a] --ex20
nub' [] = []
nub' (h:t) = if elem h t then nub' t else h : nub' t

group' :: Eq a => [a] -> [[a]]
group' [] = []
group' (h:t) = l1 : group' l2 where (l1,l2) = span ( == h) (h:t)


--partitionEither :: [Either a b] -> ([a],[b])
partitionEither lista = (as lista, bs lista)
	where 
		as ((Left x):xs) = x : as xs
		as (x:xs)        = as xs
		as otherwise     = []
		bs ((Right x):xs) = x : bs xs
		bs (x:xs)        = bs xs
		bs otherwise     = []


sufixos :: [a] -> [[a]]
sufixos [] = [[]]
sufixos (h:t) = (h:t):sufixos t

isSuffixOf :: Eq a => [a] -> [a] -> Bool
isSuffixOf [] [] = True
isSuffixOf [] l2 = True
isSuffixOf x y = if elem x (sufixos y) then True else False

partitionEithers' ::  [Either a b] -> ([a],[b])
partitionEithers' lista = (as lista, bs lista)
  where
    as ((Left x):xs)  = x : as xs
    as ((Right x):xs) = as xs
    as otherwise      = []
    bs ((Right x):xs) = x : bs xs
    bs ((Left x):xs)  = bs xs
    bs otherwise      = []

--Not workshop

data Posicao = Pos Int Int deriving (Show,Eq)

dist :: Posicao -> Posicao -> Double
dist (Pos x1 y1) (Pos x2 y2) = sqrt ( fromIntegral ( (x1 - x2)^2 + (y1 - y2)^2 ) )

group2 :: Eq a => [a] -> [[a]]
group2 (h:t) = aux h (group2 t)
	where
		aux :: Eq a => a -> [[a]] -> [[a]]
		aux x [] = [[x]]
		aux x ((y:ys) :t)
					| x == y = (x:y:ys):t
					| otherwise = [x]:(y:ys):t
group2 [] = []

pMaior :: Ord a => [a] -> Int
pMaior [] = error "Nope"
pMaior l = aux (maximum l) l 0
	where
		aux :: Eq a => a -> [a] -> Int -> Int
		aux x (h:t) n | h == x = n
					  | otherwise = aux x t (n+1)