import Data.List

--Ex 1
--a
any' :: (a -> Bool) -> [a] -> Bool
any' f [] = False
any' f (h:t) = f h || any' f t

--b
zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (x:xs) (y:ys) = (f x y):(zipWith' f xs ys)

--c
takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' f (h:t) | f h = h:takeWhile' f t
				   | otherwise = []

--d
dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' f (h:t) | f h = dropWhile' f t
				   | otherwise = h:t

--e
span' :: (a -> Bool) -> [a] -> ([a],[a])
span' f [] = ([],[])
span' f (h:t) | f h = (h:a,b)
              | otherwise = ([],h:t)
        where
        	(a,b) = span' f t

--f
deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy' _ _ [] = []
deleteBy' f n (h:t) | f n h = t
					| otherwise = h:deleteBy' f n t

--g
sortOn' :: Ord b => (a -> b) -> [a] -> [a]
sortOn' _ [] = []
sortOn' f (h:t) = insertOn' f h (sortOn' f t)
			where
				insertOn' f x [] = [x]
				insertOn' f x (h:t) | f x <= f h = x:h:t
									| otherwise = h:(insertOn' f x t)

--Ex 2
type Polinomio = [Monomio]
type Monomio = (Float,Int)

--a
selgrau :: Int -> Polinomio -> Polinomio
selgrau x [] = []
selgrau x l = filter (\n -> snd n == x) l

--b
conta :: Int -> Polinomio -> Int
conta n p = length (filter (\(c,e) -> c /= 0 && e == n) p)

--c
grau :: Polinomio -> Int
grau l = maximum (map snd (filter (\(c,e) -> c /= 0 && e /= 0) l))

--d
deriv :: Polinomio -> Polinomio
deriv l = map (\(c,e) -> (c*(fromIntegral e),e-1)) l

--e
calcula :: Float -> Polinomio -> Float
calcula x l = sum (map (\(c,e) -> c*(x^e)) l)

--f
simp :: Polinomio -> Polinomio
simp l = filter (\(c,e) -> c /= 0) l

--g
mult ::Monomio -> Polinomio -> Polinomio
mult (x,y) l = map (\(c,e) -> (x*c,e+y)) l

--h
ordena :: Polinomio -> Polinomio
ordena l = sortOn snd l

--i
normaliza :: Polinomio -> Polinomio
normaliza l = let
				a = ordena l
				b = groupBy (\x y -> snd x == snd y) a
				c = map (\p -> (sum (map fst p),snd (head p))) b
				in simp c

--j
soma :: Polinomio -> Polinomio -> Polinomio
soma l p = normaliza (l ++ p)

--k
produto :: Polinomio -> Polinomio -> Polinomio
produto l p = let
				a = map (\x -> mult x l) p
				b = foldr (++) [] a
				in normaliza b

--l
equiv :: Polinomio -> Polinomio -> Bool
equiv l p = normaliza l == normaliza p

--Ex 3
type Mat a = [[a]]

matriz = [[1,2,3],[0,4,5],[0,0,6]]

--a
dimOK :: Mat a -> Bool
dimOK l = all (\x -> length x == length (head l)) (tail l)

--b
dimMat :: Mat a -> (Int,Int)
dimMat l = (length l,length (head l))

--c
addMat :: Num a => Mat a -> Mat a -> Mat a
addMat = zipWith (zipWith (+))

--d
transpose' :: Mat a -> Mat a
transpose' [] = []
transpose' [x] = map (:[]) x
transpose' (l:ls) = zipWith (:) l (transpose ls)
{-
--e
multMat :: Num a => Mat a -> Mat a -> Mat a
multMat [] _ = []
multMat (h:t) p = let
				p' = transpose p
				a = 
-}

--f
zipWMat :: (a->b->c) -> Mat a -> Mat b -> Mat c
zipWMat _ [] _ = []
zipWMat _ _ [] = []
zipWMat f (x:xs) (y:ys) = (zipWith f x y):zipWMat f xs ys

--g
triSup :: (Num a,Eq a) => Mat a -> Bool
triSup (x:xs) = aux xs 1
		where
			a = length (x:xs)
			aux [] n = True
			aux (h:t) n | n == a = all (==0) (init h)
						| otherwise = all (==0) (take n h) && aux t (n+1)

