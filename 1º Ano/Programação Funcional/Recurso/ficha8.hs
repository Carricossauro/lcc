--Ex 1
data Frac = F {numerador :: Int, denominador :: Int}

fra :: Frac
fra = F 30 10

--a
mdc :: Int -> Int -> Int
mdc x y | x == 0 = y
		| y == 0 = x
		| x < y = mdc x (y-x)
		| otherwise = mdc (x-y) y

normaliza :: Frac -> Frac
normaliza (F x y) | y < 0 = let d = mdc (abs x) (abs y)
							in F (div (-x) d) (div (-y) d)
				  | otherwise = let d = mdc (abs x) (abs y)
				  				in F (div x d) (div y d)

--b
instance Eq Frac where
	--(==),(/=) :: Frac -> Frac -> Bool
	x == y = let
				F a b = normaliza x
				F c d = normaliza y
				in ( a == c && b == d )

--c
instance Ord Frac where
	compare x y = let
					F a c = normaliza x
					F b d = normaliza y
					in compare (a*d) (b*c)

--d
instance Show Frac where
	show x = show (numerador x) ++ "/" ++ show (denominador x)

--e
instance Num Frac where
	(F x y) * (F a b) = F (x*a) (y*b)
	(F x y) + (F a b) = normaliza (F (x*b+a*y) (y*b))
	(F x y) - (F a b) = normaliza (F (x*b-a*y) (y*b))
	negate (F x y) = F (-x) y
	abs (F x y) = F (abs x) (abs y)
	signum (F x y) = F (signum x*y) 1
	fromInteger x = F (fromIntegral x) 1

--f
funcao :: Frac -> [Frac] -> [Frac]
funcao (F x y) = filter (\(F a b) -> (F a b) > (F (2*x) y))

--Ex 2
data Exp a = Const a
		   | Simetrico (Exp a)
		   | Mais (Exp a) (Exp a)
		   | Menos (Exp a) (Exp a)
		   | Mult (Exp a) (Exp a)
--a
instance (Num a,Show a) => Show (Exp a) where
	show (Const a) = show a
	show (Simetrico a) = '(':"~" ++ show a ++ ")"
	show (Mais a b) = '(':show a ++ " + " ++ show b ++ ")"
	show (Menos a b) = '(':show a ++ " - " ++ show b ++ ")"
	show (Mult a b) = '(':show a ++ " * " ++ show b ++ ")"


--b
calcula :: Num a => Exp a -> a
calcula (Const x) = x
calcula (Simetrico x) = -(calcula x)
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y

instance (Num a,Eq a) => Eq (Exp a) where
	x == y = calcula x == calcula y

--c
instance (Num a,Eq a) => Num (Exp a) where
	x + y = Const (calcula x + calcula y)
	x - y = Const (calcula x - calcula y)
	x * y = Const (calcula x * calcula y)
	negate x = Const (- calcula x)
	abs x = Const (abs (calcula x))
	signum x = Const (signum (calcula x))
	fromInteger x = Const (fromIntegral x)

--Ex 3
data Movimento = Credito Float | Debito Float deriving Show
data Data = D Int Int Int deriving Eq
data Extrato = Ext Float [(Data,String,Movimento)]

--a
instance Ord Data where
	compare (D a1 m1 d1) (D a2 m2 d2) | a1 > a2 = GT
									  | a2 > a1 = LT
									  | m1 > m2 = GT
									  | m2 > m1 = LT
									  | d1 > d2 = GT
									  | d2 > d1 = LT
									  | otherwise = EQ


--b
instance Show Data where
	show (D a m d) = show a ++ '/':show m ++ '/':show d

d :: Extrato
d = Ext 300 [(D 2010 8 10,"COMPRA",Debito 37.5),
			 (D 2010 9 1,"LEV",Debito 60),
			 (D 2010 4 5,"DEPOSITO",Credito 2000),
			 (D 2011 1 22,"ANUIDADE",Debito 8),
			 (D 2011 1 7,"JUROS",Credito 100)]

--c
fst' :: (a,b,c) -> a
fst' (a,_,_) = a

snd' :: (a,b,c) -> b
snd' (_,b,_) = b

trd' :: (Data,String,Movimento) -> Float
trd' (_,_,Credito x) = x
trd' (_,_,Debito x) = -x

ordena :: Extrato -> Extrato
ordena (Ext a l) = Ext a (ordenado l)
				where
					ordenado :: [(Data,String,Movimento)] -> [(Data,String,Movimento)]
					ordenado [] = []
					ordenado (h:t) = inserir h (ordenado t)
					inserir :: (Data,String,Movimento) -> [(Data,String,Movimento)] -> [(Data,String,Movimento)]
					inserir x [] = [x]
					inserir (d1,b,c) ((d2,d,e):xs) | d1 < d2 = (d1,b,c):(d2,d,e):xs
												   | otherwise = (d2,d,e):(d1,b,c):xs

--d
instance Show Extrato where
	show (Ext s l) = "Saldo Anterior: " ++ show s ++
					 "\n--------------------------------------\n" ++
					 "Data -- Descricao -- Credito / Debito\n" ++ "--------------------------------------\n" ++
					 showCona l ++ "--------------------------------------" ++ 
					 "\nSaldo atual: " ++ show (saldo s l)

showCona :: [(Data,String,Movimento)] -> String
showCona [] = ""
showCona ((d,s,m):t) = show d ++ " -- " ++ show s ++ " -- " ++ show m ++ "\n" ++ showCona t

saldo :: Float -> [(Data,String,Movimento)] -> Float
saldo x l = x + (sum (map trd' l))