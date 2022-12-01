import System.Random

data Frac = F {numerador :: Int, denominador :: Int}

normaliza :: Frac -> Frac
normaliza (F x y) | y < 0 = let d = mdc (abs x) (abs y)
							in F (div (-x) d) (div (-y) d)
				  | otherwise = let d = mdc (abs x) (abs y)
				  				in F (div x d) (div y d)

mdc :: Int -> Int -> Int
mdc x y | x == 0 = y
		| y == 0 = x
		| x < y = mdc x (y-x)
		| otherwise = mdc (x-y) y

instance Eq Frac where
	f1 == f2 = let
				F n d = normaliza f1
				F x y = normaliza f2
				in (x == n && d == y)

instance Show Frac where
	show (F x y) = show x ++ "/" ++ show y

data BTree a = Empty
			 | Node a (BTree a) (BTree a)

mapBT :: (a -> b) -> BTree a -> BTree b
mapBT _ Empty = Empty
mapBT f (Node r e d) = Node (f r) (mapBT f e) (mapBT f d)

instance Functor BTree where
	fmap f Empty = Empty
	fmap f (Node r e d) = Node (f r) (fmap f e) (fmap f d)

instance Foldable BTree where
	foldr f z Empty = z
	foldr f z (Node r e d) = foldr f (foldr f (f r z) d) e

--length = foldr (\x l-> 1 + l) 0
{-
lancaDados :: IO (Int,Int)
lancaDados = do 
				x <- randomRIO (1,6)
				y <- randomRIO (1,6)
				return (x,y)
-}
--ex 3
data Movimento = Credito Float | Debito Float
data Data = D Int Int Int deriving Eq
data Extrato = Ext Float [(Data,String,Movimento)]

instance Ord Data where
	compare (D a m d) (D x y z) = if a > x then GT else
								  if a < x then LT else
								  if m > y then GT else
								  if m < y then LT else
								  if d > z then GT else LT

instance Show Data where
	show (D a m d) = show a ++ "/" ++ show m ++ "/" ++ show d

--ordena :: Extrato -> Extrato
--ordena (Ext a x) = Ext a (sortOn fste x)

fste :: (a,b,c) -> a
fste (x,_,_) = x

instance Show Movimento where
	show (Credito x) = show x
	show (Debito x) = show x

final :: Extrato -> Float
final (Ext a []) = a
final (Ext a ((_,_,Debito z):t)) = final (Ext (a-z) t)
final (Ext a ((_,_,Credito z):t)) = final (Ext (a+z) t)

show' :: [(Data,String,Movimento)] -> String
show' [] = ""
show' ((x,y,Credito z):t) = show x ++ " - " ++ show y ++ " - " ++ show z ++ "\n" ++ show' t
show' ((x,y,Debito z):t) = show x ++ " - " ++ show y ++ " - / - " ++ show z ++ "\n" ++ show' t

instance Show Extrato where
	show (Ext a l) = "Saldo anterior: " ++ show (round a) ++ "\n---------------------------------------\n"
					  ++ "Data - Descricao - Credito - Debito\n---------------------------------------\n" 
					  ++ show' l ++ "---------------------------------------\n"
					  ++ "Saldo atual: " ++ show (final (Ext a l))

d :: Extrato
d = Ext 300 [(D 2010 4 5,"DEPOSITO",Credito 2000),
			(D 2010 8 10,"COMPRA",Debito 37.5),
			(D 2010 9 1,"LEV",Debito 60),
			(D 2011 1 7,"JUROS",Credito 100),
			(D 2011 1 22,"ANUIDADE",Debito 8)]