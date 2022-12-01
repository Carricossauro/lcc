import System.Random
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe

ex1 :: [a] -> Int -> a
ex1 (h:t) 0 = h
ex1 (h:t) x = ex1 t (x-1)

data Movimento = Norte | Sul | Este | Oeste deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (Norte:t) = posicao (x+1,y) t
posicao (x,y) (Sul:t) = posicao (x-1,y) t
posicao (x,y) (Este:t) = posicao (x,y+1) t
posicao (x,y) (Oeste:t) = posicao (x,y-1) t

any' :: (a->Bool) -> [a] -> Bool
any' f [] = False
any' f (h:t) = f h || any' f t

type Mat a = [[a]]

triSup :: (Num a,Eq a) => Mat a -> Bool
triSup (h:t) = trian 1 t
			where
				trian :: (Eq a,Num a) => Int -> Mat a -> Bool
				trian _ [] = True
				trian x (h:t) | length h > x = all (==0) (take x h) && trian (x+1) t
							  | otherwise = True

{-
movimenta :: IO (Int,Int)
movimenta = do a <- getLine
			   let b = move (0,0) a
			   return b
-}
move :: (Int,Int) -> String -> (Int,Int)
move (x,y) ('N':t) = move (x+1,y) t
move (x,y) ('S':t) = move (x-1,y) t
move (x,y) ('E':t) = move (x,y+1) t
move (x,y) ('O':t) = move (x,y-1) t
move (x,y) _ = (x,y)

data Imagem = Quadrado Int
			| Mover (Int,Int) Imagem
			| Juntar [Imagem]

ex :: Imagem
ex = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5), Quadrado 4, Mover (4,3) (Quadrado 2)])

ex2 :: Imagem
ex2 = Juntar [Mover (5,5) (Quadrado 4),Mover (5,6) (Quadrado 5),Mover (9,8) (Quadrado 2)]

vazia :: Imagem -> Bool
vazia (Quadrado x) = False
vazia (Mover _ l) = vazia l
vazia (Juntar []) = True
vazia (Juntar l) = all vazia l

maior :: Imagem -> Maybe Int
maior l | vazia l = Nothing
		| otherwise = Just (maximum (quads l))
				where
					quads :: Imagem -> [Int]
					quads (Quadrado x) = [x]
					quads (Mover _ l) = quads l
					quads (Juntar l) = concat (map quads l)

instance Eq Imagem where
	x == y = let
				a = posicoes (0,0) x
				b = posicoes (0,0) y
				in (all (pertence a) b)

posicoes :: (Int,Int) -> Imagem -> [Imagem]
posicoes (x,y) (Quadrado a) = [(Mover (x,y) (Quadrado x))]
posicoes (x,y) (Mover (a,b) l) = posicoes (x+a,y+b) l
posicoes (x,y) (Juntar l) = concat (map (posicoes (x,y)) l)

pertence :: [Imagem] -> Imagem -> Bool
pertence [] _ = False
pertence ((Mover (x1,y1) (Quadrado d1)):t) (Mover (x2,y2) (Quadrado d2)) | x1==x2 && y1==y2 = d1 == d2
																	     | otherwise = pertence t (Mover (x2,y2) (Quadrado d2))

