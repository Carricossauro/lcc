import Data.Char
import Data.List

data Hora = H Int Int deriving (Show, Eq)

--hValida :: Hora -> Bool
hValida (H h m) = h >= 0 && h <= 23 && m >= 0 && m <= 59

depoisDe :: Hora -> Hora -> Bool
depoisDe (H h1 m1) (H h2 m2) = if h1 > h2 || (h1 == h2 && m1 > m2) then True else False

data Semaforo = Verde | Vermelho | Amarelo deriving (Show, Eq)

next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

stop :: Semaforo -> Bool
stop s = s == Vermelho

safe :: Semaforo -> Semaforo -> Bool
--safe x y =\ x == Vermelho || y == Vermelho
safe Vermelho _ = True
safe _ Vermelho = True
safe _ _ = False

data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show, Eq)

distOrigem :: Ponto -> Double
disOrigem (Cartesiano x y) = sqrt(x^2 + y^2)
distOrigem (Polar x _) = x

ang :: Ponto -> Double
ang (Polar _ a) = a
ang (Cartesiano x y) = atan(y/x)

data Figura = Circulo Ponto Double 
			| Retangulo Ponto Ponto
			| Triangulo Ponto Ponto Ponto deriving (Show, Eq)

poligono :: Figura -> Bool

poligono (Circulo _ _) = False
poligono (Retangulo _ _) = True
poligono (Triangulo _ _ _) = True

vertices :: Figura -> [Ponto]

vertices (Circulo x z) = []
vertices (Retangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = [Cartesiano x1 y1, Cartesiano x2 y1, Cartesiano x2 y2, Cartesiano x1 y2]
vertices (Triangulo x y z) = [x, y, z]

dist :: Ponto -> Ponto -> Double
dist (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt( (x1 - x2)^2 + (y1 - y2)^2 )
dist (Polar _ _) (Polar _ _) = 0

{-}
area :: Figura -> Double

area (Triangulo p1 p2 p3) =
	let a = dist p1 p2
		b = dist p2 p3
		c = dist p3 p1
		s = (a+b+c) / 2
	in sqrt(s*(s-a)*(s-b)*(s-c
-}

ex20 :: Eq a => [a] -> [a]
ex20 [] = []
ex20 (h:t) = if per h t then ex20 t
				else h:ex20 t

per x [] = False
per x (h:t) = if x == h then True else per x t
