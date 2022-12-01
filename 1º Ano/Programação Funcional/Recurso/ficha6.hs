--Ex 1
data BTree a = Empty
			 | Node a (BTree a) (BTree a)
			 deriving Show

--a
altura :: BTree a -> Int
altura Empty = 0
altura (Node r e d) = 1 + max (altura e) (altura d)

--b
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node r e d) = 1 + contaNodos e + contaNodos d

--c
folhas :: BTree a -> Int
folhas Empty = 1
folhas (Node r e d) = 0 + folhas e + folhas d

--d
prune :: Int -> BTree a -> BTree a
prune 1 (Node r e d) = Empty
prune _ Empty = Empty
prune n (Node r e d) = Node r (prune (n-1) e) (prune (n-1) d)

--e
path :: [Bool] -> BTree a -> [a]
path [] _ = []
path (False:t) (Node r e d) = r:path t e
path (True:t) (Node r e d) = r:path t d

--f
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node r e d) = Node r (mirror d) (mirror e)

--g
zipWithBT :: (a->b->c) -> BTree a -> BTree b -> BTree c
zipWithBT f _ Empty = Empty
zipWithBT f Empty _ = Empty
zipWithBT f (Node r1 e1 d1) (Node r2 e2 d2) = Node (f r1 r2) (zipWithBT f e1 e2) (zipWithBT f d1 d2)

--h
unzipBT :: BTree (a,b,c) -> (BTree a, BTree b, BTree c)
unzipBT Empty = (Empty,Empty,Empty)
unzipBT (Node (x,y,z) e d) = let
								(ae,be,ce) = unzipBT e
								(ad,bd,cd) = unzipBT d
								in ( Node x ae ad, Node y be bd, Node z ce cd)

--Ex 2
--a
minimo :: Ord a => BTree a -> a
minimo (Node r Empty _) = r
minimo (Node r e _) = minimo e

--b
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node r Empty d) = d
semMinimo (Node r e d) = Node r (semMinimo e) d

--c
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node r Empty d) = (r,d)
minSmin (Node r e d) = (a,Node r be d)
				where
					(a,be) = minSmin e

--d
{-
remove :: Ord a => a -> BTree a -> BTree a
remove x Empty = Empty
remove x (Node r e d) | x < r = Node r (remove x e) d
					  | x > r = Node r e (remove x d)
remove x (Node r e (Node a b c)) = Node a ()
-}

--Ex 3
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD 
			| TE 
			| MEL 
	deriving Show
data Classificacao = Ap Int
					| Re
					| Fa
	deriving (Show,Eq)
type Turma = BTree Aluno

turma :: Turma
turma = Node (3,"Tiago",ORD,Ap 15) (Node (1,"Eduardo",ORD,Ap 17) Empty (Node (2,"Afonso",ORD,Fa) Empty Empty)) (Node (4,"Ines",MEL,Ap 19) Empty (Node (6,"Luis",TE,Re) (Node (5,"Beatriz",TE,Ap 12) Empty Empty) Empty))

--a
inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum x (Node (n,_,_,_) e d) | x < n = inscNum x e
							   | x > n = inscNum x d
							   | x == n = True

--b
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome x (Node (_,n,_,_) e d) | x == n = True
								| otherwise = inscNome x e || inscNome x d

--c
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (x,n,TE,_) e d) = trabEst e ++ (x,n):trabEst d
trabEst (Node _ e d) = trabEst e ++ trabEst d

--d
nota :: Numero -> Turma -> Maybe Classificacao
nota _ Empty = Nothing
nota n (Node (a,b,_,c) e d) | n < a = nota n e
							| n > a = nota n d
							| n == a = Just c

--e
percFaltas :: Turma -> Float
percFaltas Empty = undefined
percFaltas t = let
				a = faltas t
				in ((fromIntegral a) / (fromIntegral (contaNodos t))) * 100

faltas :: Turma -> Int
faltas Empty = 0
faltas (Node (_,_,_,a) e d) | a == Fa = 1 + (faltas e) + (faltas d)
							| otherwise = faltas e + faltas d

--f
mediaAprov :: Turma -> Float
mediaAprov Empty = undefined
mediaAprov t = let
				a = notas t
				media = sum a
				in (fromIntegral media) / (fromIntegral (aprovados t))

notas :: Turma -> [Int]
notas Empty = []
notas (Node (_,_,_,Ap x) e d) = notas e ++ x:notas d
notas (Node _ e d) = notas e ++ notas d

aprovados :: Turma -> Int
aprovados Empty = 0
aprovados (Node (_,_,_,Ap _) e d) = 1 + aprovados e + aprovados d
aprovados (Node _ e d) = aprovados e + aprovados d

--g
aprovAv :: Turma -> Float
aprovAv t = let
			 (a,b) = aux t
			 aux :: Turma -> (Float,Float)
			 aux Empty = (0,0)
			 aux (Node (_,_,_,Ap _) e d) = (1+xe+xd,1+ye+yd)
			 							where
			 								(xe,ye) = aux e
			 								(xd,yd) = aux d
			 aux (Node _ e d) = (xe+xd,1+ye+yd)
			 					where
			 						(xe,ye) = aux e
									(xd,yd) = aux d
			in a / b