import System.Random
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe

inserir :: Ord a => a -> [a] -> [a]
inserir x [] = [x]
inserir x (h:t) | x > h = h:inserir x t
				| otherwise = x:h:t

catMaybes' :: [Maybe a] -> [a]
catMaybes' [] = []
catMaybes' ((Nothing):t) = catMaybes' t
catMaybes' ((Just x):t) = x:catMaybes' t

data Exp a = Const a
		   | Var String
		   | Mais (Exp a) (Exp a)
		   | Mult (Exp a) (Exp a)

c = Mais (Var "x") (Mult (Const 3) (Const 4))

instance Show a => Show (Exp a) where
	show (Const x) = show x
	show (Var x) = x
	show (Mais x y) = "(" ++ show x ++ " + " ++ show y ++ ")"
	show (Mult x y) = "(" ++ show x ++ " * " ++ show y ++ ")"

sortOn' :: Ord b => (a -> b) -> [a] -> [a]
sortOn' f [] = []
sortOn' f [x] = [x]
sortOn' f (h:t) = insertOn f h (sortOn f t)
			where
				--insertOn :: Ord b => (a->b) -> a -> [a] -> [a]
				insertOn f x [] = [x]
				insertOn f x (h:t) | f x > f h = h:insertOn f x t
								   | otherwise = x:h:t

amplitude :: [Int] -> Int
amplitude [] = 0
amplitude (h:t) = maior - menor
			where
				(maior,menor) = aux h h t
				aux :: Int -> Int -> [Int] -> (Int,Int)
				aux x y (l:ls) | l >= x = aux l y ls
							   | l <= y = aux x l ls
							   | otherwise = aux x y ls
				aux x y [] = (x,y)

parte :: [Int] -> ([Int],[Int])
parte l = let
			 x = sort l
			 y = div (last x - head x) 2
			 a = filter (\z -> last x - z <= y) x
			 b = filter (\z -> last x - z > y) x
			 in (b,a)


data Imagem = Quadrado Int
            | Mover (Int,Int) Imagem
            | Juntar [Imagem]
            deriving Show

ex :: Imagem
ex = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5), Quadrado 4, Mover (4,3) (Quadrado 2)])

conta :: Imagem -> Int
conta (Mover _ l) = conta l
conta (Juntar l) = sum (map conta l)
conta (Quadrado _) = 1

