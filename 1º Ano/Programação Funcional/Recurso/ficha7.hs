--Ex 1
data ExpInt = Const Int
			| Simetrico ExpInt
			| Mais ExpInt ExpInt
			| Menos ExpInt ExpInt
			| Mult ExpInt ExpInt

--a
calcula :: ExpInt -> Int
calcula (Const x) = x
calcula (Simetrico x) = -(calcula x)
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y

--b
infixa :: ExpInt -> String
infixa (Const x) = show x
infixa (Simetrico x) = '(':'~':infixa x ++ ")"
infixa (Mais x y) = "(" ++ infixa x ++ "+" ++ infixa y ++ ")"
infixa (Menos x y) = "(" ++ infixa x ++ "-" ++ infixa y ++ ")"
infixa (Mult x y) = "(" ++ infixa x ++ "*" ++ infixa y ++ ")"

--c
posfixa :: ExpInt -> String
posfixa (Const x) = show x
posfixa (Simetrico x) = posfixa x ++ " ~"
posfixa (Mais x y) = posfixa x ++ " " ++ posfixa y ++ " +"
posfixa (Menos x y) = posfixa x ++ " " ++ posfixa y ++ " -"
posfixa (Mult x y) = posfixa x ++ " " ++ posfixa y ++ " *"

--Ex 2
data RTree a = R a [RTree a] deriving Show

arvore :: Num a => RTree a
arvore = (R 3 [R 2 [],R 4 [R 2 [], R 2 [R 4 []]],R 6 []])

--a
soma :: Num a => RTree a -> a
soma (R a l) = a + sum (map soma l)

--b
altura :: RTree a -> Int
altura (R _ []) = 1
altura (R _ l) = 1 + maximum (map altura l)

--c
prune :: Int -> RTree a -> RTree a
prune 1 (R x l) = R x []
prune x (R a l) = R a (map (prune (x-1)) l)

--d
mirror :: RTree a -> RTree a
mirror (R r l) = R r (reverse (map mirror l))

--e
postorder :: RTree a -> [a]
postorder (R a []) = [a]
postorder (R a l) = concat (map postorder l) ++ [a]

--Ex 3
data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show
data LTree a = Tip a | Fork (LTree a) (LTree a) deriving Show

ltree :: Num a => LTree a
ltree = Fork (Fork (Tip 5) (Fork (Fork (Tip 1) (Tip 3)) (Fork (Tip 0) (Tip 9)))) (Fork (Tip 5) (Tip 2))

--a
ltSum :: Num a => LTree a -> a
ltSum (Tip x) = x
ltSum (Fork e d) = ltSum e + ltSum d

--b
listaLT :: LTree a -> [a]
listaLT (Tip x) = [x]
listaLT (Fork e d) = listaLT e ++ listaLT d

--c
ltHeight :: LTree a -> Int
ltHeight (Tip _) = 0
ltHeight (Fork e d) = 1 + max (ltHeight e) (ltHeight d)

--Ex 4
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)

ftree :: (Num a, Num b) => FTree a b
ftree = No 1 (No 5 (No 9 (Leaf 1) (Leaf 1)) (No 0 (Leaf 12) (No 9 (Leaf 1) (Leaf 5)))) (Leaf 6)

--a
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf b) = (Empty,Tip b)
splitFTree (No r e d) = (Node r ae ad,Fork be bd)
					where
						(ae,be) = splitFTree e
						(ad,bd) = splitFTree d
						