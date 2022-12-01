data FS = Fich Nome
		| Dir Nome [FS]
		deriving Show

type Nome = String

t :: FS
t = Dir "a" [Fich "b", Dir "c" [Fich "d",Fich "e"], Fich "f"]

quantosF :: FS -> Int
quantosF (Fich _) = 1
quantosF (Dir _ []) = 0
quantosF (Dir _ l) = sum (map quantosF l)
--quantosF (Dir _ l) = foldr (\h t' -> (quantoF h) + t')

fichs :: FS -> [Nome]
fichs (Fich n) = [n]
fichs (Dir _ l) = concat (map fichs l)
--fichs (Dir _ l) = concatMap fichs l
--fichs (Dir _ l) = foldr (\h t' -> ((fichs h) ++ t') [] l)

procura :: Nome -> FS -> Bool
procura x (Fich n) = n == x
procura x (Dir _ l) = any (procura x) l
--procura (Dir _ l) = or (map (procura x) l)
{-
find :: FS -> Nome -> Maybe [Nome]
find (Fich a) n | n == a = Just [a]
				| otherwise = Nothing
find (Dir d l) n = case (catMaybe (map (\f -> find f n) l) ) of
					[] -> Nothing
					(h:t) -> Just d:h
-}

--IMPORTANTE
--CLASSES
--Necessário definir a classe e as suas instâncias

--Definiçao da classe
{-
class Eq a where
	(==) :: a -> a -> Bool
	(/=) :: a -> a -> Bool

instance Eq Bool where
	(==) :: Bool -> Bool -> Bool
	True == True = True
	False == False = True
	_ == _ = False
	(/=) :: Bool -> Bool -> Bool
	True /= True = False
	False /= False = False
	_ /= _ = True

instance Eq a => Eq (Maybe a) where
	(==) :: Maybe a -> Maybe a -> Bool
	Nothing == Nothing = True
	Just x == Just y = x == y
	_ == _ = False
	(/=) :: Maybe a -> Maybe a -> Bool
	Nothing /= Nothing = False
	Just x /= Just y = x /= y
	_ /= _ = True
-}

data ExpInt = Const Int
			| Simetrico ExpInt
			| Mais ExpInt ExpInt
			| Menos ExpInt ExpInt
			| Mult ExpInt ExpInt

--ex 1a
calcula :: ExpInt -> Int
calcula (Const x) = x
calcula (Simetrico x) = - calcula x
calcula (Mais x y) = calcula x + calcula y
calcula (Menos x y) = calcula x - calcula y
calcula (Mult x y) = calcula x * calcula y

--ex 1b
infixa :: ExpInt -> String
infixa (Const x) = show x
infixa (Simetrico x) = '~':infixa x
infixa (Mais x y) = "(" ++ infixa x ++ "+" ++ infixa y ++ ") "
infixa (Menos x y) = "(" ++ infixa x ++ "-" ++ infixa y ++ ") "
infixa (Mult x y) = "(" ++ infixa x ++ "*" ++ infixa y ++ ") "

--ex 1c
posfixa :: ExpInt -> String
posfixa (Const x) = show x
posfixa (Simetrico x) = posfixa x ++ " ~"
posfixa (Mais x y) = posfixa x ++ " " ++ posfixa y ++ " +"
posfixa (Menos x y) = posfixa x ++ " " ++ posfixa y ++ " -"
posfixa (Mult x y) = posfixa x ++ " " ++ posfixa y ++ " *"

--ex 2
data RTree a = R a [RTree a]

--ex 2a
soma :: Num a => RTree a -> a
soma (R a trees) = a + sum (map soma trees)

--ex 2b
altura :: RTree a -> Int
altura (R a l) = 1 + maximum (map altura l)

--ex 2c
prune :: Int -> RTree a -> RTree a
prune 1 (R a l) = R a []
prune x (R a l) = R a (map (prune (x-1)) l)

tr :: Num a => RTree a
tr = (R 2 [R 3 [R 7 [],R 4 []], R 7 [R 8 [R 9 []]],R 10 []])

--ex 2d
mirror :: RTree a -> RTree a
mirror (R a l) = R a (reverse (map mirror l))

--ex 2e
postorder :: RTree a -> [a]
postorder (R a l) = [a] ++ (concatMap postorder l)

data LTree a = Tip a
			 | Fork (LTree a) (LTree a)

--ex 3a
ltSum :: Num a => LTree a -> a
ltSum (Tip a) = a
ltSum (Fork e d) = ltSum e + ltSum d

--ex 3b
listaLT :: LTree a -> [a]
listaLT (Tip a) = a:[]
listaLT (Fork e d) = listaLT e ++ listaLT d

--ex 3c
ltHeight :: LTree a -> Int
ltHeight (Tip a) = 1
ltHeight (Fork e d) = 1 + max (ltHeight e) (ltHeight d)

data BTree a = Empty
			 | Node a (BTree a) (BTree a)

data FTree a b = Leaf b
			 | No a (FTree a b) (FTree a b)
			 deriving Show
--ex 4a
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf b) = (Empty, Tip b)
splitFTree (No r e d) = (Node r xe xd, Fork ye yd)
				where
					(xe,ye) = splitFTree e
					(xd,yd) = splitFTree d

--ex 4b
joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees Empty (Fork _ _) = Nothing
joinTrees (Node _ _ _) (Tip _) = Nothing
joinTrees Empty (Tip a) = Just (Leaf a)
joinTrees (Node a e d) (Fork x y) = Just (No a (ex) (dy))
							where
								ex = maybe (joinTrees e x)
								dy = maybe (joinTrees d y)
								maybe :: Maybe a -> a
								maybe (Just a) = a
