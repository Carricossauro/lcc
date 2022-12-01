import System.Random
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe
import Data.List
import Data.Ord
import Data.Either

--Ex 1
enumFromTo' :: Int -> Int -> [Int]
enumFromTo' x y | x == y = [x]
				| otherwise = x:enumFromTo' (x+1) y

--Ex 2
enumFromThenTo' :: Int -> Int -> Int -> [Int]
enumFromThenTo' x y z | x == z = [x]
					  | x > z = []
					  | otherwise  = x:enumFromThenTo' (x+(y-1)) y z

--Ex 3
(+++) :: [a] -> [a] -> [a]
(+++) [] l = l
(+++) (h:t) l = h:(t +++ l)

--Ex 4
(!!!) :: [a] -> Int -> a
(!!!) (h:t) 0 = h
(!!!) (h:t) x = t !!! (x-1)

--Ex 5
reverse' :: [a] -> [a]
reverse' [] = []
reverse' (h:t) = reverse t ++ [h]


--Ex 6
take' :: Int -> [a] -> [a]
take' _ [] = []
take' 1 (h:t) = [h]
take' x (h:t) = h:take (x-1) t

--Ex 7
drop' :: Int -> [a] -> [a]
drop' _ [] = []
drop' 1 (h:t) = t
drop' x (h:t) = drop (x-1) t

--Ex 8
zip' :: [a] -> [b] -> [(a,b)]
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x,y):zip' xs ys

--Ex 9
elem' :: Eq a => a -> [a] -> Bool
elem' _ [] = False
elem' x (h:t) = x == h || elem' x t

--Ex 10
replicate' :: Int -> a -> [a]
replicate' 1 a = [a]
replicate' x a = a:replicate (x-1) a

--Ex 11
intersperce' :: a -> [a] -> [a]
intersperce' _ [] = []
intersperce' _ [h] = [h]
intersperce' a (h:x:t) = h:a:intersperce' a (x:t)

--Ex 12
group' :: Eq a => [a] -> [[a]]
group' [] = []
group' l = aux l : group' ( drop (length ( aux l)) l )
	where
		aux :: Eq a => [a] -> [a]
		aux [x] = [x]
		aux (h:x:t) = if h == x then h:aux (x:t) else [h]

--Ex 13
concat' :: [[a]] -> [a]
concat' [] = []
concat' (h:t) = h ++ concat' t

--Ex 14
inits' :: [a] -> [[a]]
inits' [] = [[]]
inits' l = inits' (init l) ++ [l]

--Ex 15
tails' :: [a] -> [[a]]
tails' [] = [[]]
tails' l@(h:t) = [l] ++ tails' t

--Ex 16
isPrefixOf' :: Eq a => [a] -> [a] -> Bool
isPrefixOf' (h:t) [] = False
isPrefixOf' [] _ = True
isPrefixOf' (h:t) (x:xs) = h == x && isPrefixOf' t xs

--Ex 17
isSuffixOf' :: Eq a => [a] -> [a] -> Bool
isSuffixOf' [] _ = True
isSuffixOf' _ [] = False
isSuffixOf' l1@(h:t) l2@(x:xs) | length l1 == length l2 = h == x && isSuffixOf' t xs
							   | otherwise = isSuffixOf' l1 xs

--Ex 18
isSubsequenceOf' :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf' (h:t) [] = False
isSubsequenceOf' [] _ = True
isSubsequenceOf' (h:t) (x:xs) | x == h = isSubsequenceOf' t xs
							  | otherwise = isSubsequenceOf' (h:t) xs

--Ex 19
elemIndices' :: Eq a => a -> [a] -> [Int]
elemIndices' x l = aux 0 x l
			where
				aux :: Eq a => Int -> a -> [a] -> [Int]
				aux n x [] = []
				aux n x (h:t) | h == x = n:aux (n+1) x t
							  | otherwise = aux (n+1) x t

--Ex 20
nub' :: Eq a => [a] -> [a]
nub' l = aux l []
		where
			aux :: Eq a => [a] -> [a] -> [a]
			aux (h:t) [] = aux t [h]
			aux [] l = l
			aux (h:t) l | elem h l = aux t l
						| otherwise = aux t (h:l)

--Ex 21
delete' :: Eq a => a -> [a] -> [a]
delete' x [] = []
delete' x (h:t) | x == h = t
				| otherwise = h:delete' x t

--Ex 22
(///) :: Eq a => [a] -> [a] -> [a]
(///) l [] = l
(///) [] _ = []
(///) l (h:t) = (delete h l) /// t

--Ex 23
union' :: Eq a => [a] -> [a] -> [a]
union' l [] = l
union' l (h:t) | elem h l = union' l t
			   | otherwise = union' (l ++ [h]) t

--Ex 24
intersect' :: Eq a => [a] -> [a] -> [a]
intersect' l [] = []
intersect' [] _ = []
intersect' (h:t) l | elem h l = h:intersect' t l
			       | otherwise = intersect' t l

--Ex 25
insert' :: Ord a => a -> [a] -> [a]
insert' l [] = [l]
insert' x (h:t) | x <= h = x:h:t
				| otherwise = h:insert' x t

--Ex 26
unwords' :: [String] -> String
unwords' [] = []
unwords' (h:t) = h ++ unwords t

--Ex 27
unlines' :: [String] -> String
unlines' [] = []
unlines' (h:t) = h ++ '\n':unlines' t

--Ex 28
pMaior :: Ord a => [a] -> Int
pMaior l = maior 0 l
		where
			maior :: Ord a => Int -> [a] -> Int
			maior x [l] = x
			maior x (h:y:t) | h >= y = maior x (h:t) 
							| otherwise = maior (x+1) (y:t)

--Ex 29
temRepetidos :: Eq a => [a] -> Bool
temRepetidos [] = False
temRepetidos (h:t) = elem h t  || temRepetidos t

--Ex 30
algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (h:t) | isDigit h = h:algarismos t
				 | otherwise = algarismos t

algarismos' :: [Char] -> [Char]
algarismos' = filter isDigit

--Ex 31
posImpares :: [a] -> [a]
posImpares [] = []
posImpares l = aux 0 l
			where
				aux :: Int -> [a] -> [a]
				aux _ [] = []
				aux 0 (h:t) = aux 1 t
				aux x (h:t) | mod x 2 /= 0 = h:aux (x+1) t
							| otherwise = aux (x+1) t

--Ex 32
posPares :: [a] -> [a]
posPares [] = []
posPares l = aux 0 l
			where
				aux :: Int -> [a] -> [a]
				aux _ [] = []
				aux 0 (h:t) = h:aux 1 t
				aux x (h:t) | mod x 2 == 0 = h:aux (x+1) t
							| otherwise = aux (x+1) t

--Ex 33
isSorted' :: Ord a => [a] -> Bool
isSorted' [] = True
isSorted' [h] = True
isSorted' (h:x:t) = x >= h && isSorted' (x:t)

--Ex 34
iSort' :: Ord a => [a] -> [a]
iSort' [] = []
iSort' (h:t) = insert h (iSort' t)

--Ex 35
menor :: String -> String -> Bool
menor [] (h:t) = True
menor _ [] = False
menor (x:xs) (y:ys) | ord x < ord y = True
					| ord x == ord y = menor xs ys
					| otherwise = False

--Ex 36
type MSet a = [(a,Int)]

elemMSet :: Eq a => a -> MSet a -> Bool
elemMSet _ [] = False
elemMSet n ((x,y):t) = n == x || elemMSet n t

--Ex 37
lengthMSet :: MSet a -> Int
lengthMSet [] = 0
lengthMSet ((x,y):t) = y + lengthMSet t

--Ex 38
converteMSet :: MSet a -> [a]
converteMSet [] = []
converteMSet ((x,y):t) = replicate y x ++ converteMSet t

--Ex 39
insereMSet :: Eq a => a -> MSet a -> MSet a
insereMSet n [] = [(n,1)]
insereMSet n ((x,y):t) | n == x = (x,y+1):t
					   | otherwise = (x,y):insereMSet n t

--Ex 40

--Ex 41

--Ex 42
partitionEithers' :: [Either a b] -> ([a],[b])
partitionEithers' ((Left a):t) = (a:x,y)
					where (x,y) = partitionEithers' t
partitionEithers' ((Right b):t) = (x,b:y)
					where (x,y) = partitionEithers' t

--Ex 43
