import System.Random

--bingo :: IO ()

randomEL :: [a] -> IO (a,[a])
randomEL l = do p <- randomRIO (1,(length l) -1);
				let (x,y) = splitAt p l;
				return ((head y),x ++ (tail y))

hello :: IO ()
hello = do putStr "Hello\n"
