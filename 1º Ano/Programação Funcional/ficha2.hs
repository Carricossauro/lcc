import Data.List
import Data.Char

type Monomio = (Float,Int)
type Polinomio = [Monomio]

--deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ( (x,y) : t ) = if y * x > 0 then (y * x, y -1):deriv t
						else deriv t