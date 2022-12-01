import System.Random
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe

intersect' :: Eq a => [a] -> [a] -> [a]
intersect' l [] = []
intersect' [] _ = []
intersect' (h:t) l | elem h l = h:intersect t l
				  | otherwise = intersect t l

tails' :: [a] -> [[a]]
tails' [] = [[]]
tails' (h:t) = (h:t):tails t

type ConjInt = [Intervalo]
type Intervalo = (Int,Int)

elems :: ConjInt -> [Int]
elems [] = []
elems l = concat (map (\(x,y) -> nums x y) l)
		where 
			nums :: Int -> Int -> [Int]
			nums x y | x == y = [x]
				     | x < y = x:nums (x+1) y
				     | otherwise = []

geraConj :: [Int] -> ConjInt
geraConj [] = []
geraConj l = let
				a = groupBy (\ x y -> y == x + 1) l
				b = map int a
				in b


int :: [Int] -> Intervalo
int l = (head l,last l)

data Contacto = Casa Integer
			  | Trab Integer
			  | Tlm Integer
			  | Email String
			  deriving Show

type Nome = String
type Agenda = [(Nome,[Contacto])]

acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail x e [] = [(x,[(Email e)])]
acrescEmail x e ((h,l):t) | x == h = (h,(Email e):l):t
						  | otherwise = (h,l):acrescEmail x e t


verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n ((h,l):t) | n == h = Just (ems l)
					  | otherwise = verEmails n t
				where
					ems :: [Contacto] -> [String]
					ems ((Email x):t) = x:ems t
					ems (h:t) = ems t
					ems [] = []

consulta :: [Contacto] -> ([Integer],[String])
consulta [] = ([],[])
consulta ((Email em):t) = (a,em:b)
				where (a,b) = consulta t
consulta ((Casa x):t) = (x:a,b)
				where (a,b) = consulta t
consulta ((Trab x):t) = (x:a,b)
				where (a,b) = consulta t
consulta ((Tlm x):t) = (x:a,b)
				where (a,b) = consulta t

data RTree a = R a [RTree a] deriving (Show,Eq)

paths :: RTree a -> [[a]]
paths (R a []) = [[a]]
paths (R a l) = map (\x -> a:x) (concat (map paths l))

tree :: RTree Integer
tree = R 1 [R 2 [], R 3 [R 4 [R 5 [], R 6 []]], R 7 []]

unpaths :: Eq a => [[a]] -> RTree a
unpaths [[h]] = R h []
unpaths [(h:t)] = R h [(unpaths [t])]
unpaths ((h:t):l) = R h ((unpaths [t]):(map unpaths [l]))