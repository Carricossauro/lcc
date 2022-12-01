union' :: Ord a => [a] -> [a] -> [a]
union' [] l = l
union' l [] = l
union' (x:xs) (y:ys) | x == y = union' xs ys
					 | x < y = x:union' xs (y:ys)
					 | x > y = y:x:union' xs ys