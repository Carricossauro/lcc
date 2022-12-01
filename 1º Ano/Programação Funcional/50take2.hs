import Data.List
import Data.Ord
import Data.Either

ex1 :: Int -> Int -> [Int]
--enumFromTo 1 5 --> [1,2,3,4,5]
ex1 x n | x <= n = x:ex1 (x+1) n
		| otherwise = []

ex2 :: Int -> Int -> Int -> [Int]
--enumFromThenTo 1 3 10 --> [1,3,5,7,9]
ex2 x n p | x < p = x:ex2 (x+(n-1)) n p
		  | otherwise = []

ex3 :: [a] -> [a] -> [a]
--(++) [1,2,3] [10,20,30] --> [1,2,3,10,20,30]
ex3 [] l = l
ex3 (h:t) l = h:ex3 t l

ex4 :: [a] -> Int -> a
--(!!) [10,20,30] 1 --> 20
ex4 (h:t) x | x == 0 = h
			| x > 0 = ex4 t (x-1)
			| otherwise = error "A posição não existe"
ex4 [] _ = error "A posição não existe"

ex5 :: [a] -> [a]
--reverse [1,2,3] [3,2,1]
ex5 l = rev l [] 
rev :: [a] -> [a] -> [a]
rev [] l = l
rev (h:t) l = rev t (h:l)

ex6 :: Int -> [a] -> [a]
--take 2 [10,20,30] --> [10,20]
ex6 n (h:t) | n > 0 = h:ex6 (n-1) t
ex6 _ _ = []

ex7 :: Int -> [a] -> [a]
--drop 2 [10,20,30] --> [30]
ex7 n (h:t) | n > 0 = ex7 (n-1) t
ex7 _ l = l

--Ex 8
--Constroi lista de pares a partir de duas listas
zip' :: [a] -> [a] -> [(a,a)]
zip' [] _ = []
zip' _ [] = []
zip' (h:t) (x:y) = (h,x):zip' t y

--Ex 9
--Determina se a um elemento pertence a uma lista
elem' :: Eq a => a -> [a] -> Bool
elem' n [] = False
elem' n (h:t) = h == n || elem' n t

--Ex 10 
--Constroi uma lista com 'n' elementos, todos iguais a x
replicate' :: Int -> a -> [a]
replicate' 0 x = []
replicate' n x = x : replicate' (n-1) x

--Ex 11
--Dado um elemento e uma lista, insere o elemento dado entre cada da lista
intersperce' :: a -> [a] -> [a]
intersperce' x [h] = [h]
intersperce' x (h:t) = h : x : intersperce' x t

--Ex 12 
--Agrupa elementos iguais e consecutivos
group' :: Eq a => [a] -> [[a]]
group' [] = []
group' l = aux l : group' ( drop (length ( aux l)) l )
	where
		aux :: Eq a => [a] -> [a]
		aux [x] = [x]
		aux (h:x:t) = if h == x then h:aux (x:t) else [h]

--Ex 13
--Concatena as listas de uma lista
concat' :: [[a]] -> [a]
concat' [] = []
concat' ((h:[]) :t) = h:concat' t
concat' ((h:x)  :t) = h:concat' (x:t)

--Ex 14
--Caulula os prefixos de uma lista
inits' :: [a] -> [[a]]
inits' l = []:aux l []
	where
		aux :: [a] -> [a] -> [[a]]
		aux [] l = []
		aux (h:t) l = (reverse (h:l) ) : aux t (h:l)

--Ex 15
--Calcula a lista de sufixos de uma lista
tails' :: [a] -> [[a]]
tails' [] = [[]]
tails' (h:t) = (h:t):tails' t

--Ex 16
--Testa se uma lista é prefixo de outra
isPrefixOf' :: Eq a => [a] -> [a] -> Bool
isPrefixOf' [x] [y] = if x == y then True else False
isPrefixOf' (x:xs) (y:ys) = if x == y then isPrefixOf' xs ys else False
isPrefixOf' _ _ = True

--Ex 17
--Testa se uma lista é um sufixo da outra
isSuffixOf' :: Eq a => [a] -> [a] -> Bool
isSuffixOf' l1 l2 = elem l1 (tails' l2)

--Ex 18
--Testa se os elementos de uma lista ocorren noutra pela mesma ordem relativa
--isSubsequenceOf [10,30] [10,20,30,40] --> True
--isSubsequenceOf [20,10] [10,20,30,40] --> False
isSubsequenceOf' :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf' [] _ = True
isSubsequenceOf' _ [] = False
isSubsequenceOf' (x:xs) (y:ys) = if x == y then isSubsequenceOf' xs ys
									else isSubsequenceOf' (x:xs) ys

--Ex 19
--Calcula a lista de posições em que um elemento ocorre
elemIndices' :: Eq a => a -> [a] -> [Int]
elemIndices' n l = aux n l 0
	where
		aux :: Eq a => a -> [a] -> Int -> [Int]
		aux n (h:t) p = if n == h then p:aux n t (p+1) else aux n t (p+1)
		aux n [] p = []

--Ex 20
--Calcula a lista com os elementos dados, sem repetição
nub' :: (Ord a,Eq a) => [a] -> [a]
nub' [] = []
nub' (h:t) = if elem h t then sort (nub' t) else sort (h:nub' t)

--Ex 21
--Remove a primeira ocorrência de um elemento
delete' :: Eq a => a -> [a] -> [a]
delete' _ [] = []
delete' x (h:t) = if x == h then t else h:delete' x t

--Ex 22
--Remove da primeira lista as primeiras ocorrências dos elementos da segunda lista
(//) :: Eq a => [a] -> [a] -> [a]
(//) l [] = l
(//) (y:ys) (x:xs) = (//) (aux x (y:ys)) xs
	where
		aux :: Eq a => a -> [a] -> [a]
		aux x [] = []
		aux x (h:t) = if x == h then t else h:aux x t

--Ex 23
--Acrescenta à primeira lista os elementos da seguna que não ocorrerem na primeira
union' :: Ord a => [a] -> [a] -> [a]
union' l [] = l
union' l1 (h:t) = if elem h l1 then union' l1 t else sort (h:union' l1 t)

--Ex 24
--Remove da primeira lista os elementos que não pertencem à segunda
intersect' :: Eq a => [a] -> [a] -> [a]
intersect' [] l = []
intersect' (x:xs) l = if elem x l then x:intersect' xs l else intersect' xs l

--Ex 25
--Insere ordenadamente um elemento numa lista
insert' :: (Ord a, Eq a) => a -> [a] -> [a]
insert' n (h:x:t) | n <= h = n:h:x:t
				  | n > h && n <= x = h:n:x:t
				  | otherwise = h:insert' n (x:t)
insert' n (h:t) = h:n:t
insert' n _ = [n]

insert2 :: (Ord a, Eq a) => a -> [a] -> [a]
insert2 n (h:t) | n <= h = n:h:t
				| otherwise = h:insert2 n t
insert2 n [] = [n]

--Ex 26
--Junta todas as Strings dadas em uma só, separadas por espaços
unwords' :: [String] -> String
unwords' (h:t) = h ++ " " ++ unwords' t
unwords' [] = []

--Ex 27
--Junts todas as Strings dadas em uma só, separadas por '\n' (new lines)
unline' :: [String] -> String
unline' (h:t) = h ++ "\n" ++ unline' t
unline' [] = []

--Ex 28
--Retorna a posição onde se encontra o maior elemento da lista
{-
pMaior :: Ord a => [a] -> Int
pMaior l = aux (sort l) 0
	where
		aux :: Ord a => [a] -> Int -> Int
		aux (h:x:t) pos = if h >= x then aux (h:t) pos else aux (x:t) (pos+1)
		aux (h:[]) pos = pos
-}

pMaior :: Ord a => [a] -> Int
pMaior l = aux l (maximum l) 0
	where
		aux :: Ord a => [a] -> a -> Int -> Int
		aux (h:t) x n | h == x = n
					  | otherwise = aux t x (n+1)

pMaior2 :: Ord a => [a] -> Int
pMaior2 l = aux l 0 0
	where
		aux :: Ord a => [a] -> Int -> Int -> Int
		aux [h,x] n p | h >= x = n
				   	  | otherwise = p
		aux (h:x:t) n p | h >= x = aux (h:t) n (p+1)
						| h < x = aux (x:t) (p+1) (p+1)

--Ex 29
--Testa se uma lista tem elementos repetidos
temRepetidos :: Eq a => [a] -> Bool
temRepetidos [] = False
temRepetidos (h:t) = elem h t || temRepetidos t

--Ex 30
--Retira os algarismos de umas lista de carateres
algarismos :: [Char] -> [Char]
algarismos (h:t) = if elem h ['0'..'9'] then h:algarismos t else algarismos t
algarismos [] = []

--Ex 31
--Determina os elementos de uma lista que ocorrem nas posições ímpares (0 é par)
posImpares :: [a] -> [a]
posImpares [] = []
posImpares l = aux l 0
	where
		aux :: [a] -> Int -> [a]
		aux (h:t) n | odd n = h : aux t (n+1)
				    | otherwise = aux t (n+1)
		aux [] _ = []

--Ex 32
--Determina os elementos da lista que ocorrem nas posições pares (0 é par)
posPares :: [a] -> [a]
posPares (h:x:t) = h:posPares (t)
posPares [x] = [x]
posPares _ = []

--Ex 33
--Testa se uma lista está em ordem crescente
isSorted :: (Ord a, Eq a) => [a] -> Bool
isSorted (h:x:t) = if h <= x then isSorted (x:t) else False
isSorted _ = True

--Ex 34
--Ordena uma lista
--inserir um elemento ordenadamente na lista --> insert :: Ord a => a -> [a] -> [a]
iSort :: Ord a => [a] -> [a]
iSort (h:t) = insert h (iSort t)
iSort [] = []

--Ex 35
--Retorna "True" se a primeira String for menor que a segunda
menor :: String -> String -> Bool
menor [] (h:t) = True
menor (h:t) [] = False
menor (x:xs) (y:ys) = menor xs ys
menor _ _ = False

--Ex 36
--Testa se um elemento pertence a um multi-conjunto
--elemMSet 'a' [('b',2), ('a',4), ('c',1)] --> True
--elemMSet 'd' [('b',2), ('a',4), ('c',1)] --> False
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet a [] = False
elemMSet a ( (x,y) :t) = if a == x then True else elemMSet a t

--Ex 37
--Calcula o tamanho de um multi-conjunto
lengthMSet :: [(a,Int)] -> Int
lengthMSet [] = 0
lengthMSet ( (x,y) :t) = y + lengthMSet t

--Ex 38
--Converte um multi-conjunto na lista dos seus elementos
converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ( (x,y) :t) = print x y ++ converteMSet t
	where 
		print :: a -> Int -> [a]
		print x 0 = []
		print x n = x:print x (n-1)

--Ex 39
--Acrescenta um elemento a um multi-conjunto
--insereMSet 'c' [('b',2),('a',4),('c',1)] --> [('b',2),('a',4),('c',2)]
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet a [] = [(a,1)]
insereMSet a ( (x,y) :t) | a == x = (x,y+1):t
						 | otherwise = (x,y):insereMSet a t

--Ex 40
--Remove um elemento a um multi-conjunto
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet a ( (x,y) :t) | a == x = (x,y-1):t
						 | otherwise = (x,y):removeMSet a t

--Ex 41
--Dada uma lista ordenada por ordem crescente, dá o seu multi-conjunto
--constroiMSet "aaabccc" --> [('a',3),('b',1),('c',3)]
constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet l = aux [] l
	where
		aux :: Eq a => [(a,Int)] -> [a] -> [(a,Int)]
		aux l [] = l
		aux ( (x,y) :m) (h:t)  | h == x = aux ((x,y+1):m) t
						       | otherwise = (x,y):aux m (h:t)

--Ex 42
--Divide uma lista Eithers num lista de pares
partitionEtihers :: [Either a b] -> ([a],[b])
partitionEtihers lista = (ls lista, rs lista)
	where
		ls ((Left l):t) = l:ls t
		ls ((Right _):t) = ls t
		ls otherwise = []
		rs ((Right r):t) = r:rs t
		rs ((Left _):t) = rs t
		rs otherwise = []

--Ex 43
--Coleciona os elementos de tipo a de uma listas de Maybes
catMaybe :: [Maybe a] -> [a]
catMaybe ((Just x) :t) = x:catMaybe t
catMaybe ((Nothing):t) = catMaybe t
catMaybe otherwise = []

--Movimento representa movimento de um robot
data Movimento = Norte | Sul | Este | Oeste deriving (Show,Eq)

--Ex 44
--Calcula a posição final do robot, dada  aposição inicial e o movimento
posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) (h:t) 
			| h == Norte = posicao (x,y+1) t
			| h == Sul = posicao (x,y-1) t
			| h == Este = posicao (x+1,y) t
			| h == Oeste = posicao (x-1,y) t
posicao (x,y) [] = (x,y)

--Ex 45
--Dadas as posições inicial e final, dá a lista de movimentos
caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x1,y1) (x2,y2) = (vert y1 y2) ++ (hori x1 x2)
	where
		hori :: Int -> Int -> [Movimento]
		hori x1 x2 | x1 < x2 = Este:hori (x1+1) x2
				   | x2 < x1 = Oeste:hori (x1-1) x2
				   | otherwise = []
		vert :: Int -> Int -> [Movimento]
		vert y1 y2 | y1 < y2 = Norte:vert (y1+1) y2
				   | y2 < y1 = Sul:vert (y1-1) y2
				   | otherwise = []

--Ex 46
--Determina se uma lista de movimentos é só vertical (Norte ou Sul)
vertical :: [Movimento] -> Bool
vertical [h] = (h == Norte || h == Sul)
vertical (h:t) = (h == Norte || h == Sul) && vertical t

--Ex 47
--Determina qual coordenada está mais perto da origem
data Posicao = Pos Int Int deriving (Show,Eq)

maisCentral :: [Posicao] -> Posicao
maisCentral [x] = x
maisCentral (h:t) = if (min distancia (dist (maisCentral t))) == distancia then h else maisCentral t
	where
		distancia = dist h
		dist :: Posicao -> Double
		dist (Pos x y) = sqrt (fromIntegral (x^2 + y^2))

--Ex 48
--Recebe uma posicao e uma lista e as posicoes vizinhas da lista à inicial
vizinhos :: Posicao -> [Posicao] -> [Posicao]
vizinhos p (h:t) = if elem h (viz p) then h:vizinhos p t else vizinhos p t
vizinhos p [] = []

viz :: Posicao -> [Posicao]
viz (Pos x y) = [p1,p2,p3,p4,p5,p6,p7,p8]
	where
		p1 = Pos (x+1) y
		p2 = Pos (x-1) y
		p3 = Pos x (y+1)
		p4 = Pos x (y-1)
		p5 = Pos (x+1) (y+1)
		p6 = Pos (x-1) (y+1)
		p7 = Pos (x+1) (y-1)
		p8 = Pos (x-1) (y-1)

--Ex 49
--Testa se as posiçoes de uma lista têm a mesma ordenada
mesmaOrdenada :: [Posicao] -> Bool
mesmaOrdenada ( (Pos x y) : (Pos n h) :t) = if h == y then mesmaOrdenada ((Pos n h):t) else False
mesmaOrdenada [h] = True

--Ex 50
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

--Testa se o semaforo é seguro
seguro :: [Semaforo] -> Bool
seguro [] = True
seguro (h:t) = if cores (h:t) > 1 then False else True
cores (Verde:t) = 1 + cores t
cores (Amarelo:t) = 1 + cores t
cores (Vermelho:t) = 0 + cores t
cores [] = 0