import Data.Char
import Data.List
import Data.Either
import Data.Maybe

ex1 :: Int -> Int -> [Int] --enumFromTo
ex1 x y | x == y = [x]
ex1 x y | x < y = x:(ex1 (x+1) y)

alternativa :: Int -> Int -> [Int]
alternativa x y = if x == y then [x] else x:(ex1 (x+1) y)

ex2 :: Int -> Int -> Int -> [Int] --enumFromThenTo
ex2 x y z | x == z = [x]
ex2 x y z | x > z = []
ex2 x y z | x < z = x:(ex2 (x + (y-1)) y z)

ex3 :: [a] -> [a] -> [a] -- (++)
ex3 [] l2 = l2
ex3 (h:t) l2 = h:ex3 t l2

ex4 :: [a] -> Int -> [a] --(!!)
ex4 (h:t) 0 = [h]
ex4 (h:t) x = ex4 t (x-1)

ex5 :: [a] -> [a] --reverse
ex5 [] = []
ex5 (h:t) = rev [] (h:t)

rev :: [a] -> [a] -> [a]
rev l [] = l
rev l (h:t) = rev (h:l) t

rev' :: [a] -> [a]
rev' [] = []
rev' (h:t) = rev' t ++ [h]

ex6 :: Int -> [a] -> [a] --take
ex6 n _ | n == 0 = []
ex6 n (h:t) = h:ex6 (n-1) t

ex7 :: Int -> [a] -> [a]
ex7 n l | length l <= n = []
ex7 n (h:t) | n == 0 = t
ex7 n (h:t) = ex7 (n-1) t

ex8 :: [a] -> [b] -> [(a,b)]
ex8 (h1:[]) (h2:t2) = [(h1,h2)]
ex8 (h1:t1) (h2:[]) = [(h1,h2)]
ex8 (h1:t1) (h2:t2) = (h1,h2):ex8 t1 t2

ex9 :: Eq a => a -> [a] -> Bool
ex9 x [] = False
ex9 x (h:t) | x == h = True
ex9 x (h:t) = ex9 x t

ex10 :: Int -> a -> [a]
ex10 n x | n == 0 = []
ex10 n x = x:ex10 (n-1) x

ex11 :: Int -> [Int] -> [Int]
ex11 _ (h:[]) = [h]
ex11 n (h:t) = h:(n:ex11 n t)

--Exercício 12
ex12 :: Eq a => [a] -> [[a]]
ex12 [] = []
ex12 l = aux:ex12 (drop (length aux) l)
	where aux = ex12_aux l

ex12_aux [x] = [x]
ex12_aux (x:h:t) = if x == h then x:ex12_aux (h:t) else [x]

--Fim

ex13 :: Eq a => [[a]] -> [a]
ex13 [] = []
ex13 ( (h:[]) :t) = h:ex13 t
ex13 ( (h:x)  :t) = h:ex13 (x:t)

ex14 :: [a] -> [[a]]
ex14 [] = []
ex14 l = []:aux14 l []

aux14 [] _= []
aux14 (h:t) l = ( ex5 (h:l) ):aux14 t (h:l)

ex15 :: [a] -> [[a]]
ex15 [] = [[]]
ex15 (h:t) = (h:t):ex15 t

ex16 :: Eq a => [a] -> [a] -> Bool
ex16 [] _ = False
ex16 _ [] = False
ex16 (h:[]) (x:y) = h == x
ex16 (h:t) (x:y) | h == x = ex16 t y

ex17 :: Eq a => [a] -> [a] -> Bool
ex17 [] _ = True
ex17 _ [] = False
ex17 l (x:y) | length l == length (x:y) = aux17 l (x:y)
	    	 | length l /= length (x:y) = ex17 l y

aux17 (h:[]) (x:[]) = True
aux17 (h:t) (x:y) = if h == x then aux17 t y else False

ex18 :: Eq a => [a] -> [a] -> Bool
ex18 [] _ = True
ex18 _ [] = False
ex18 (x:xs) (y:ys) = aux18 (x:xs) (y:ys)

aux18 _ [] = False
aux18 [] _ = False
aux18 (x:xs) (y:ys) = if x == y then ex18 xs ys else aux18 (x:xs) ys

ex19 :: Eq a => a -> [a] -> [Int]
ex19 x [] = []
ex19 x (h:t) = aux19 0 x (h:t)

aux19 _ _ [] = []
aux19 n x (h:t) = if x == h then n:aux19 (n + 1) x t
					else aux19 (n + 1) x t

ex20 :: Eq a => [a] -> [a]
ex20 (h:t) = f (h:t) []

f [] l = ex5 l
f (h:t) l = if (per h l) then f t l
				else f t (h:l)

per x [] = False
per x (h:t) = if x == h then True else per x t

ex21 :: Eq a => a -> [a] -> [a]
ex21 x (h:t) = aux21 x (h:t) []

aux21 x [] l = l
aux21 x (h:t) l = if x == h then t
					else h:aux21 x t l

ex22 :: Eq a => [a] -> [a] -> [a]
ex22 (h:t) (x:y) = if h == x then ex22 t y
					else h:ex22 t (x:y)
ex22 [] _ = []
ex22 l [] = l

ex23 :: Eq a => [a] -> [a] -> [a]
ex23 l [] = l
ex23 l (x:y) = if per x l then ex23 l y else ex23 (aux23 x l) y

aux23 x [] = [x]
aux23 x (h:t) = h:aux23 x t

ex24 :: Eq a => [a] -> [a] -> [a]

ex24 [] _ = []
ex24 (h:t) l = if per h l then h:ex24 t l
				else ex24 t l

ex25 :: (Eq a, Ord a) => a -> [a] -> [a]
ex25 n [] = []
ex25 n (x:[]) = if n <= x then n:x:[] else x:n:[]
ex25 n (h:x:t) | h > n = n:h:x:t
			   | h <= n && x >= n = h:n:x:t
			   | otherwise = h:ex25 n (x:t)

ex26 :: [String] -> String
ex26 [h] = h
ex26 [] = ""
ex26 (h:t) = ex3 ( ex3 h " ") (ex26 t)

ex27 :: [String] -> String
ex27 [h] = ex3 h "\n"
ex27 [] = ""
ex27 (h:t) = ex3 ( ex3 h "\n") (ex27 t)

ex28 :: Ord a => [a] -> Int
ex28 [] = 0
ex28 l = aux28 l (maximum l) 0

aux28 (h:t) x n | h == x = n
				| otherwise = aux28 t x (n+1)

ex29 :: Eq a => [a] -> Bool
ex29 [] = False
ex29 (h:t) = (per h t) || ex29 t

ex30 :: [Char] -> [Char]
ex30 [] = []
ex30 (h:t) = if per h l then h:ex30 t else ex30 t
				where l = ['1','2','3','4','5','6','7','8','9','0']

ex31 :: [a] -> [a]
ex31 [] = []
ex31 l = aux31 l 0

aux31 [] _ = []
aux31 (h:t) p = if (odd p) then h:aux31 t ps else aux31 t ps
					where ps = p + 1

ex32 :: [a] -> [a]
ex32 [] = []
ex32 l = aux32 l 0

aux32 [] _ = []
aux32 (h:t) p | p == 0 = h:aux32 t (p + 1)
aux32 (h:t) p = if (par p) then h:aux32 t ps else aux32 t ps
					where ps = p + 1

par p = mod p 2 == 0

ex33 :: Ord a => [a] -> Bool
ex33 (h:x:t) = (h <= x) && ex33 (x:t)
ex33 _ = True

ex34 :: Ord a => [a] -> [a]
ex34 (h:x:t) = if h <= x then h:ex34 (x:t) else x:ex34 (h:t)
ex34 [] = []
ex34 (h:[]) = [h]

ex35 :: String -> String -> Bool
ex35 (h:t) (x:y) | ord h == ord x = ex35 t y
				 | ord h > ord x = False
				 | ord h < ord x = True
ex35 [] (x:t) = True
ex35 (x:t) [] = False
ex35 [] [] = False

ex36 :: Eq a => a -> [(a, Int)] -> Bool
ex36 n [] = False
ex36 n ( (x,y) :t) = if x == n then True else ex36 n t

ex37 :: [(a,Int)] -> Int
ex37 [] = 0
ex37 ( (x,y) :t) = y + ex37 t

ex38 :: [(a,Int)] -> [a]
ex38 [] = []
ex38 (h:t) = (++) (aux38 h) (ex38 t)

aux38 (x,y) = if y >= 1 then x:aux38 (x,(y-1)) else []

ex39 :: Eq a => a -> [(a,Int)] -> [(a,Int)]
ex39 n [] = []
ex39 n ( (x,y) :t) = if n == x then (x, (y+1) ):t else (x,y):ex39 n t

ex40 :: Eq a => a -> [(a,Int)] -> [(a,Int)]
ex40 n [] = []
ex40 n ( (x,y) :t) = if n == x then 
								if y >= 2 then (x,y-1):t
									else t
						else (x,y):ex40 n t

ex41 :: Eq a => [a] -> [(a,Int)]
ex41 [] = []
ex41 l = aux41 l 1

aux41 (h:x:t) n = if h == x then aux41 (x:t) (n+1) else (h,n):aux41 (x:t) 1
aux41 (x:t) n = [(x,n)]
aux41 _ n = []

ex42 :: [Either a b] -> ([a],[b])
ex42 x = (lefts x, rights x)

{-
ex42a :: [Either a b] -> ([a],[b])º
ex42a (x:t) | isLeft x = ([x],[]):ex42a t
			| isRight x = ([],[x]):ex42a t


ex43 :: [Maybe a] -> [a]
ex43 (h:t) | isJust h = [fromJust h]:ex43 t
ex43 _ = []

-}

--data Movimentos de um robot
data Movimento = Norte | Sul | Este | Oeste deriving (Show,Eq)

ex44 :: (Int,Int) -> [Movimento] -> (Int,Int)
ex44 (x,y) [] = (x,y)
ex44 (x,y) (h:t) | h == Norte = ex44 (x, y+1) t
				 | h == Sul = ex44 (x, y-1) t
				 | h == Este = ex44 (x+1, y) t
				 | h == Oeste = ex44 (x-1, y) t

ex45 :: (Int,Int) -> (Int,Int) -> [Movimento]
ex45 x y | x == y = []
ex45 (xi,yi) (xf,yf) = (++) (vertical xi xf) (horizontal yi yf)

vertical i f = let n = f - i
				in if f > i then vezes n Norte
					else if f < i then vezes (-n) Sul
						else []

horizontal i f = let n = f - i
					in if f > i then vezes n Este
						else if f < i then vezes (-n) Oeste
							else []

vezes 0 _ = []
vezes x m = m:vezes (x-1) m

ex46 :: [Movimento] -> Bool
ex46 [] = False
ex46 [h] = h == Norte || h == Sul
ex46 (h:t) | h == Norte = ex46 t
		   | h == Sul = ex46 t
		   | otherwise = False

--data 'posicao' de um robot numa grelha
data Posicao = Pos Int Int deriving (Show,Eq)

ex47 :: [Posicao] -> Posicao
ex47 [] = error "nope"
ex47 [h] = h
ex47 (h:x:t) | distOrigem h > distOrigem x = ex47 (x:t)
			 | distOrigem h < distOrigem x = ex47 (h:t)

distOrigem :: Posicao -> Double
distOrigem (Pos x y) = sqrt ( fromIntegral ( x^2 + y^2 ))

ex48 :: Posicao -> [Posicao] -> [Posicao]
ex48 _ [] = []
ex48 x (y:t) = if dist x y <= h then y:ex48 x t 
			   	else ex48 x t
			   	where h = dist (Pos 1 1) (Pos 2 2)


dist :: Posicao -> Posicao -> Double
dist (Pos x1 y1) (Pos x2 y2) = sqrt ( fromIntegral((x1-x2)^2 + (y1-y2)^2) )

ex49 :: [Posicao] -> Bool
ex49 ( (Pos x y):(Pos x1 y1):[] ) = y == y1
ex49 ( (Pos x y):(Pos x1 y1):t ) = if y == y1 then ex49 ((Pos x1 y1):t) else False

--data Semaforo
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

ex50 :: [Semaforo] -> Bool
ex50 (h:x:[]) | h == x = if h == Vermelho then True else False
			  | otherwise = if h /= Vermelho && x /= Vermelho then False else True


ex50 (h:x:t) | h == x = if h == Vermelho then ex50 (x:t) else False
			 | otherwise = if h /= Vermelho && x /= Vermelho then False else ex50 (x:t)
ex50 [] = False
ex50 _ = True