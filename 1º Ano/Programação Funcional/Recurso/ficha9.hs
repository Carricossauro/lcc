import System.Random
import Control.Monad
import Data.Char
import Data.List
import Data.Maybe

{-
randomEL :: [a] -> IO (a,[a])
randomEL l = if True then
			 do	p <- randomRIO (0,length (l-1))
				let (x,y:ys) = splitAt p l
				return (y, x ++ ys)
			  else return (0,[])
-}

randomE :: [a] -> IO a
randomE l = do p <- randomRIO (0,length - 1)
			   return (l!!p)