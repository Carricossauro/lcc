import System.Random
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe

isSorted :: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (h:x:t) | h > x = False
				 | otherwise = isSorted (x:t)

inits' :: [a] -> [[a]]
inits' l = []:map reverse (reverse (aux (reverse l)))
		where
			aux :: [a] -> [[a]]
			aux [] = []
			aux l = l:aux (tail l)

maximumMB :: Ord a => [Maybe a] -> Maybe a
maximumMB [Just x] = Just x
maximumMB ((Nothing):t) = maximumMB t
maximumMB (a:(Nothing):t) = maximumMB (a:t)
maximumMB ((Just x):(Just y):t) | x >= y = maximumMB ((Just x):t)
								| otherwise = maximumMB ((Just y):t)
maximumMB _ = Nothing

data LTree a = Tip a | Fork (LTree a) (LTree a)

l = Fork (Tip 0) (Fork (Fork (Tip 3) (Tip 2)) (Fork (Tip 1) (Fork (Tip 0) (Tip 9))))

listaLT :: LTree a -> [a]
listaLT (Tip a) = [a]
listaLT (Fork a b) = listaLT a ++ listaLT b

instance Show a => Show (LTree a) where
	show (Tip x) = show x
	show x = show' x 0
			where
				show' (Tip a) b = replicate b '.' ++ show a
				show' (Fork a b) c = show' a (c+1) ++ '\n':show' b (c+1)


maxSumInit :: (Num a,Ord a) => [a] -> a
maxSumInit l = aux (sum l) (inits l)
			where
				aux x [] = x
				aux x (h:t) = let y = sum h in if x > y then aux x t else aux y t

type RelP a = [(a,a)]
type RelL a = [(a,[a])]
type RelF a = [([a],a->[a])]

t :: RelP Int
t = [(1,3),(1,4),(2,1),(2,4),(2,5),(3,7),(4,7),(5,7),(6,5),(7,6)]
p :: RelL Int
p = [(1,[3,4]),(2,[1,4,5]),(3,[7]),(4,[7]),(5,[7]),(6,[5]),(7,[6])]

convLP :: RelL a -> RelP a
convLP l = concat (map junta l)
		where junta (x,xs) = map (\y -> (x,y)) xs

convPL :: (Eq a,Ord a) => RelP a -> RelL a
convPL l = let
			  a = sortOn fst l
			  b = groupBy (\(x,_) (y,_) -> x == y) a
			  k = map junta b
			  junta :: [(a,a)] -> (a,[a])
			  junta x = (fst (head x),(map snd x))
			  in k

convFP :: Eq a => RelF a -> RelP a
convFP (l,f) = concat (map g l)
			where
				g = map (\y -> (x,y)) (filter (\a -> elem a (f x)) l)

