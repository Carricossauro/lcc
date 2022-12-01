import Data.Char

isLow :: Char -> Bool

isLow x = if y >= (ord 'a') && y <= (ord 'z') then True else False
	where y = ord x

isDig :: Char -> Bool

isDig x = if y >= (ord '0') && y <= (ord '9') then True else False
	where y = ord x

isAl :: Char -> Bool

isAl x = if (y >= (ord 'A') && y <= (ord 'z')) then True else False
	where y = ord x