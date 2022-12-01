import Data.Char
import Data.List

data Hora = H Int Int deriving (Show,Eq)
type Etapa = (Hora,Hora)
type Viagem = [Etapa]

--Determina se a hora é valida
valida :: Hora -> Bool
valida (H h m) = (h <= 23 && h >= 0 && m <= 59 && m >= 0)

--Indica qual das horas é maior
maior :: Hora -> Hora -> Hora
maior (H h1 m1) (H h2 m2) = if valida (H h1 m1) && valida (H h2 m2) then
	if h1 > h2 then (H h1 m1) else
		if h2 > h1 then (H h2 m2) else
			if h1 == h2 then
				if m1 >= m2 then (H h1 m1) else
					if m2 > m1 then (H h2 m2) else (H 0 0)
					else (H 0 0)
					else (H 0 0)

--Transforma horas em minutos
hm :: Hora -> Int
hm (H h m) = (h * 60) + m

--Transforma minutos em horas
mh :: Int -> Hora
mh x = H (div x 60) (mod x 60)

--Calcula a diferença entre duas horas (em minutos)
dif :: Hora -> Hora -> Int
dif (H h1 m1) (H h2 m2) = if min > 0 then min else -min
	where min = hm (H h1 m1) - hm (H h2 m2)

--Adicionar um número de minutos a uma hora
adi :: Int -> Hora -> Hora
adi min (H h m) = mh (min + hm (H h m))

--Testa se unma etapa está bem construída - 1a
eta :: Etapa -> Bool
eta (h1,h2)
	| valida h1 && valida h2 = if (maior h1 h2 == h2) then True else False
	| otherwise = False

--Testa se a viagem está bem construída - 1b
via :: Viagem -> Bool
via [] = True
via (h:t) = if eta h == True then 
	if via t then True 
		else False 
	else False

--Calcula a hora de partida e chegada de uma viagem - 1c
horas :: Viagem -> [Hora]
horas ( ((h1),(h2)) : t) = h1:che t:[]

che :: Viagem -> Hora
che (h:[]) = snd(h)
che (h:t) = che t

--Calcula o tempo de viagem 1d
tempo :: Viagem -> Int
tempo (h:[]) = aux h
tempo (h:t) | via (h:t) = aux h + tempo t

aux (h1,h2) = dif h1 h2

--Calcula o tempo de espera entre etapas 1e
espera :: Viagem -> Int
espera (h:[]) = 0
espera (h:x:t) | via (h:x:t) = aux_espera h x + espera (x:t)

aux_espera :: Etapa -> Etapa -> Int
aux_espera (_,h2) (h3,_) = dif h3 h2

--Calula o tempo total de viagem 1f
total :: Viagem -> Int
total k = tempo k + espera k

data Ponto = Cartesiano Double Double
           | Polar Double Double deriving (Show, Eq)

distOrigem :: Ponto -> Double
disOrigem (Cartesiano x y) = sqrt(x^2 + y^2)
distOrigem (Polar x _) = x

ang :: Ponto -> Double
ang (Polar _ a) = a
ang (Cartesiano x y) = atan(y/x)

type Poligonal = [Ponto]

--Calcula o comprimento de uma linha poligonal 2a
comp :: Poligonal -> Double
comp (h:[]) = 0
comp (h:x:t) = (dist h x) + comp (x:t)

dist :: Ponto -> Ponto -> Double
dist (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt( (x1 - x2)^2 + (y1 - y2)^2 )

--Testa se uma linha  poligonal é ou não fechada 2b
fechada :: Poligonal -> Bool
fechada l = (head l == last l)

