import Data.List
import Data.Char

mySplit :: Int -> [a] -> ([a],[a])
mySplit 0 l = ([],l)
mySplit n [] = ([],[])
mySplit n (h:t) = let (x,y) = mySplit (n - 1) t
					in (h:x,y)

myZip :: [a] -> [b] -> [(a,b)]
myZip (x:xs) (y:ys) = (x,y):zip xs ys
myZip _ _ = []

myUnzip :: [(a,b)] -> ([a],[b])
myUnzip [] = ([],[])
myUnzip ( (x,y):t ) = (x:p1,y:p2)
						where (p1,p2) = myUnzip t

myElem :: Eq a => a -> [a] -> Bool
myElem x [] = False
myElem x (h:t) = (x == h) || elem x t

myElemO :: Ord a => a -> [a] -> Bool
myElemO x [] = False
myElemO x (h:t) | x == h = True
				| x > h = myElemO x t
				| x < h = False