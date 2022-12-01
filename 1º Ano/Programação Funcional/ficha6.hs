data BTree a = Empty
			| Node a (BTree a) (BTree a)
			deriving Show

l = Node 1 (Node 2 (Node 5 Empty Empty) (Node 4 Empty (Node 9 (Node 10 Empty Empty) (Node 11 Empty Empty)))) (Node 3 (Node 6 (Node 7 Empty Empty) (Node 8 Empty Empty)) Empty)

x = Node 10 (Node 7 (Node 2 Empty Empty) (Node 8 Empty Empty)) (Node 42 Empty Empty) --Lista de procura

--Ex 1
--a
altura :: BTree a -> Int
altura (Empty) = 0
altura (Node a b1 Empty) = 1 + altura b1
altura (Node a Empty b2) = 1 + altura b2
altura (Node a b1 b2) | altura b1 > altura b2 = 1 + altura b1
					  | otherwise = 1 + altura b2

--b
contaNodes :: BTree a -> Int
contaNodes Empty = 0
contaNodes (Node _ b1 b2) = 1 + contaNodes b1 + contaNodes b2

--c
folhas :: BTree a -> Int
folhas Empty = 1
folhas (Node _ Empty b2) = 1 + folhas b2
folhas (Node _ b1 Empty) = 1 + folhas b1
folhas (Node _ b1 b2) = folhas b1 + folhas b2

--d
prune :: Int -> BTree a -> BTree a
prune _ Empty = Empty
prune x (Node a b1 b2) | x == 1 = (Node a Empty Empty)
					   | x > 0 = (Node a (prune (x-1) b1) (prune (x-1) b2))

--e
path :: [Bool] -> BTree a -> [a]
path _ Empty = []
path [] _ = []
path (True:t) (Node a b1 b2) = a:(path t b2)
path (False:t) (Node a b1 b2) = a:(path t b1)

--f
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node a b1 b2) = Node a (mirror b2) (mirror b1)

--g
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT f Empty b2 = Empty
zipWithBT f b1 Empty = Empty
zipWithBT f (Node r1 e1 d1) (Node r2 e2 d2) = Node (f r1 r2) (zipWithBT f e1 e2) (zipWithBT f d1 d2)

--h
unzipBT :: BTree (a,b,c) -> (BTree a, BTree b, BTree c)
unzipBT Empty = (Empty , Empty , Empty)
unzipBT (Node (a,b,c) e d) = (Node a x1 x2, Node b y1 y2,Node c z1 z2)
							where ((x1,y1,z1),(x2,y2,z2)) = (unzipBT e, unzipBT d)

--Ex 2
--a
minimo :: Ord a => BTree a -> a
minimo (Node r Empty d) = r
minimo (Node r e d) = minimo e

--b
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node r Empty d) = Empty
semMinimo (Node r e d) = Node r (semMinimo e) d

--c
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node r Empty d) = (r,d)
minSmin (Node r e d) = (x,Node r y d)
				where (x,y) = minSmin e

--maximo
mSm :: Ord a => BTree a -> (a,BTree a)
mSm (Node r e Empty) = (r,e)
mSm (Node r e d) = (x,Node r e y)
				where (x,y) = mSm d

--d
remove :: Ord a => a -> BTree a -> BTree a
remove _ Empty = Empty
remove x (Node r Empty d) = d
remove x (Node r e d) | x < r = remove x e
					  | x > r = remove x d
					  | otherwise = removeRaiz (Node r e d)

removeRaiz :: Ord a => BTree a -> BTree a
removeRaiz (Node r Empty d) = d
removeRaiz (Node r e d) = Node x e' d
						where (x,e') = mSm e

type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD 
			| TE 
			| MEL 
	deriving Show
data Classificacao = Aprov Int
					| Rep
					| Faltou
	deriving Show
type Turma = BTree Aluno --arvore binaria de procura (ordenada por numero)

t :: BTree Aluno
t = Node (2,"Joao",ORD,Aprov 15) (Node (1,"Tiago",TE,Aprov 19) Empty Empty) (Node (3,"Diogo",MEL,Rep) Empty (Node (4,"Manel",TE,Faltou) Empty Empty))

--a
inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum x (Node (num,_,_,_) e d) = x == num || inscNum x e || inscNum x d

--b
inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome x (Node (_,nome,_,_) e d) = x == nome || inscNome x e || inscNome x d

--c
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (num,nome,r,_) e d) | trabalha r = trabEst e ++ [(num,nome)] ++ trabEst d
								  | otherwise = trabEst e ++ trabEst d

trabalha :: Regime -> Bool
trabalha TE = True
trabalha _ = False

--d
nota :: Numero -> Turma -> Maybe Classificacao
nota x Empty = Nothing
nota x (Node (num,_,_,cla) e d) | x == num = Just cla
								| x < num = nota x e
								| x > num = nota x d

--e
percFaltas :: Turma -> Float
percFaltas Empty = undefined
percFaltas t = ((fromIntegral faltas) / (fromIntegral alunos)) * 100
			where
				(faltas,alunos)= faltInsc t
				faltInsc :: Turma -> (Int,Int)
				faltInsc Empty = (0,0)
				faltInsc (Node (_,_,_,Faltou) e d) = (1+x+z,1+y+w)
										where
											(x,y) = faltInsc e
											(z,w) = faltInsc d
				faltInsc (Node (_,_,_,_) e d) = (0+x+z,1+y+w)
										where
											(x,y) = faltInsc e
											(z,w) = faltInsc d

--f
mediaAprov :: Turma -> Float
mediaAprov Empty = undefined
mediaAprov t = ((fromIntegral notas) / (fromIntegral aprovados))
			where
				(notas,aprovados) = nAp t
				nAp Empty = (0,0)
				nAp (Node (_,_,_,Aprov n) e d) = (n+x+z,1+y+w)
										where
											(x,y) = nAp e
											(z,w) = nAp d
				nAp (Node (_,_,_,_) e d) = (0+x+z,0+y+w)
										where
											(x,y) = nAp e
											(z,w) = nAp d

--g
aprovAv :: Turma -> Float
aprovAv Empty = undefined
aprovAv t = ((fromIntegral aprovados)/(fromIntegral alunos)) * 100
			where
				(aprovados,alunos) = apAl t
				apAl :: Turma -> (Int,Int)
				apAl Empty = (0,0)
				apAl (Node (_,_,_,Aprov _) e d) = (1+x+z,1+y+w)
											where
												(x,y) = apAl e
												(z,w) = apAl d
				apAl (Node (_,_,_,Rep) e d) = (0+x+z,1+y+w)
											where
												(x,y) = apAl e
												(z,w) = apAl d
				apAl (Node (_,_,_,_) e d) = (0+x+z,0+y+w)
											where
												(x,y) = apAl e
												(z,w) = apAl d
