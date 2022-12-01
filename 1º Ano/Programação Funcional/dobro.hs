dobro :: Integer -> Integer
dobro x = 2 * x

sexo :: Float -> Float
sexo x = x/7 * x + 3

variavel :: Float -> Float
variavel x = x * 2 / 3 + 2.5

perimetro :: Float -> Float
perimetro r = r * pi * 2

gays :: Float -> Float
gays x = l * 3 + 5 / p 
 	where
 		l = x - 1
 		p = x + 6

dist (x1, y1) (x2, y2) = sqrt (x' * x' + y' * y') --Funciona
	where
		x' = x1 - x2
		y' = y1 - y2
		
primUlt :: [a] -> (a, a)
primUlt l = (head l, last l)

multiplo :: Int -> Int -> Bool
multiplo x y = (mod x y == 0) -- if (mod x y == 0) then True else False

max2 :: Int -> Int -> Int
max2 x y = if (x > y) then x else y

max3 :: Int -> Int -> Int -> Int
max3 x y z = max2 x (max2 y z)

raizes a b c = if (nraizes a b c== 0) then []
	else if (nraizes a b c == 1)
		then [-b / (2 * a)]
		else if (nraizes a b c == 2)
			then [(-b + sqrt(b^2 - 4 * a * c)) / 2 * a, (-b - sqrt(b^2 - 4 * a * c)) / 2 * a]
			else []

truncaImpar :: [a] -> [a]
truncaImpar l = if (mod (length l) 2 == 0)
	then l
	else tail l

nraizes :: Double -> Double -> Double -> Int
nraizes a b c = if (b^2 - 4 * a * c < 0) then 0
	else if (b^2 - 4 * a * c == 0) then 1
		else 2


type Hora = (Int, Int)

--Ex 3a
horas :: Hora -> Bool
horas x = if fst (x) <= 23 && fst (x) >= 0 && snd (x) <= 59 && snd (x) >= 0
	then True
	else False

--Ex 3b
horacom :: Hora -> Hora -> Hora
horacom x y = if horas (x) && horas (y) then
	if fst (x) > fst (y) then x else
	if fst (y) > fst (x) then y else
		if fst (x) == fst (y) then
			if snd (x) > snd (y) then x else
				if snd (x) < snd (y) then y else (0,0)
				else (0,0)
				else (0,0)

--Ex 3c
hormin :: Hora -> Int
hormin x = ((fst (x) * 60)+ snd (x))

--Ex 3d
minhor :: Double -> Double
minhor x = (x / 60)

--Ex 3e
mini :: Hora -> Hora -> Int
mini x y = if hormin (x) > hormin (y) then (hormin (x) - hormin (y))
	else if hormin (x) < hormin (y) then (hormin (y) - hormin (x)) else 0

{- Ex 3f
adi :: Hora -> Int -> Hora
adi h x =

	Não sei fazer 3f    -}