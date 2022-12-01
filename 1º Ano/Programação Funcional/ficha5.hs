import Data.List

any' :: (a -> Bool) -> [a] -> Bool
any' f [] = False
any' f (h:t) = f h || any' f t

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' f (x:xs) (y:ys) = (f x y):zipWith' f xs ys
zipWith' _ _ _ = []

takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' f (h:t) | f h = h:takeWhile' f t
				   | otherwise = []
takeWhile' _ _ = []

dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' f (h:t) | f h = dropWhile' f t
				   | otherwise = h:t
dropWhile' _ _ = []

span' :: (a -> Bool) -> [a] -> ([a],[a])
span' f (h:t) | f h = (h:a,b)
						where (a,b) = span' f t
span' _ l = ([],l)

deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy' f x (h:t) | f x h = t
					| otherwise = h:deleteBy' f x t

sortOn' :: Ord b => (a -> b) -> [a] -> [a]
sortOn' f [] = []
sortOn' f (h:t) = insertOn f h (sortOn' f t)
					where 
						insertOn f x [] = [x]
						insertOn f x (y:ys) | f x <= f y = x:y:ys
											| otherwise = y:insertOn f x ys

type Polinomio = [Monomio]
type Monomio = (Float,Int)

selgrau :: Int -> Polinomio -> Polinomio
selgrau x [] = []
selgrau x l = filter (\(c,e) -> e == x) l 

conta :: Int -> Polinomio -> Int
conta n p = length (filter (\(x,y) -> y == n && x /= 0) p)

grau :: Polinomio -> Int
grau p = maximum (map snd g)
		where g = filter (\(x,y) -> y /= 0 && x /= 0) p

deriv :: Polinomio -> Polinomio
deriv p = filter (\(c,e) -> c/=0) (map (\(c,e) -> (c*fromIntegral e,e-1)) p)

calcula :: Float -> Polinomio -> Float
calcula x p = sum (map (\(c,e) -> c * x^e) p)

simp :: Polinomio -> Polinomio
simp p = filter (\(x,y) -> x/=0) p

mult :: Monomio -> Polinomio -> Polinomio
mult (x,y) p = map (\(c,e) -> (c*x,y+e)) p

ordena :: Polinomio -> Polinomio
ordena p = sortOn snd p

normaliza :: Polinomio -> Polinomio
normaliza p = let
				ps = ordena p
				pg = groupBy (\x y -> snd x == snd y) ps
				p' = map (\l -> (sum (map fst l), snd (head l))) pg
				in filter (\x -> fst x /= 0) p'


soma :: Polinomio -> Polinomio -> Polinomio
soma p1 p2 = normaliza (p1 ++ p2)

produto :: Polinomio -> Polinomio -> Polinomio
produto l (h:t) = normaliza ((mult h l) ++ (produto l t))
produto _ _ = []

equiv :: Polinomio -> Polinomio -> Bool
equiv p1 p2 = all (elem' p22) p11
			where
				p11 = normaliza p1
				p22 = normaliza p2
				elem' [] (x,y) = False
				elem' (h:t) (x,y) = (y == snd h && x == fst h) || elem' t (x,y)

type Mat a = [Linha]
type Linha = [Int]

dimOk :: Mat a -> Bool
dimOk (h:t) = all (== length h) (map length t)

dimMat :: Mat a -> (Int,Int)
dimMat (h:t) = (length (h:t),length h)

addMat :: Mat a -> Mat a -> Mat a
addMat = zipWith (zipWith (+))	

transpose' :: Mat a -> Mat a
transpose' [] = []
transpose' [x] = map (:[]) x
transpose' (l:ls) = zipWith (:) l (transpose ls)

multMat :: Mat a -> Mat a -> Mat a
multMat m1 m2 = let
					ponto p1 p2 = sum (zipWith (*) (map head p2) p1 )