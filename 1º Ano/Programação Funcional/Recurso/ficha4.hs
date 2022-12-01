import Data.Char

--Ex 1
a1 = [x | x <- [1..20], mod x 2 == 0, mod x 3 == 0] -- 6,12,18
b1 = [x | x <- [y | y <- [1..20], mod y 2 == 0], mod x 3 == 0] --6,12,18
c1 = [(x,y) | x <- [1..20], y <- [1..20], x+y==30]
d1 = [sum [y | y <- [1..x], odd y] | x <- [1..10]]

--Ex 2
a2 = [2^x | x <-[0..10]]
b2 = [(x,y) | x <- [1..5], y <- [1..5], x+y==6]
c2 = [[1..x] | x <- [1..5]]
d2 = [replicate x 1 | x <- [1..5]]
e2 = [product [y | y <- [1..x]] | x <- [1..6]]

--Ex 3
digitAlpha :: String -> (String, String)
digitAlpha [] = ([],[])
digitAlpha l = aux3 l ([],[])
	where
		aux3 :: String -> (String,String) -> (String,String)
		aux3 [] (l,n) = (reverse l,reverse n)
		aux3 (h:t) (l,n) | isAlpha h = aux3 t (h:l,n)
						 | isDigit h = aux3 t (l,h:n)

--Ex 4
nzp :: [Int] -> (Int,Int,Int)
nzp [] = (0,0,0)
nzp l = aux4 l (0,0,0)
	where
		aux4 :: [Int] -> (Int,Int,Int) -> (Int,Int,Int)
		aux4 [] (n,z,p) = (n,z,p)
		aux4 (h:t) (n,z,p) | h < 0 = aux4 t (n+1,z,p)
						   | h == 0 = aux4 t (n,z+1,p)
						   | h > 0 = aux4 t (n,z,p+1)

--Ex 5
divMod' :: Integral a => a -> a -> (a,a)
divMod' x y = aux5 x y (0,0)
	where
		aux5 :: Integral a => a -> a -> (a,a) -> (a,a)
		aux5 x y (d,r) | y > x && x == 0 = (d,0)
					   | y > x && x /= 0 = (d,y)
					   | x >= y = aux5 (x-y) y (d+1,0)

--Ex 6
fromDigits :: [Int] -> Int
fromDigits [] = 0
fromDigits [x] = x * 10
fromDigits l = aux6 l (length l - 1)
	where
		aux6 :: [Int] -> Int -> Int
		aux6 [] len = 0
		aux6 (h:t) len = h*10^len + aux6 t (len - 1)

--Ex 7


--Ex 8
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = aux8 1 1 2
	where
		aux8 :: Int -> Int -> Int -> Int
		aux8 m x y | m == n = x
				   | otherwise = aux8 (m+1) y (x+y)