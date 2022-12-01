data Ponto = P Double Double deriving (Show,Eq)

type Poligonal = [Ponto]

data Figura = Circulo Ponto Double 
			| Retangulo Ponto Ponto
			| Triangulo Ponto Ponto Ponto deriving (Show, Eq)

dist :: Ponto -> Ponto -> Double
dist (P x1 y1) (P x2 y2) = sqrt( (x1 - x2)^2 + (y1 - y2)^2 )


area :: Figura -> Double
area (Triangulo p1 p2 p3) = let 
							a = (dist p1 p2)
							b = (dist p2 p3)
							c = (dist p3 p1)
							s = (a+b+c) / 2 --Semi-perimetro
							in sqrt ((s*(s-a)*(s-b)*(s-c))) --Formula de Heron
area (Circulo c r) = pi * r^2
area (Retangulo (P x1 y1) (P x2 y2)) = ( sqrt(x1)^2 + sqrt(x2)^2 ) * ( sqrt(y1)^2 + sqrt(y2)^2 )


comp :: Poligonal -> Double
comp (h:x:t) = dist h x + comp (x:t)
comp _ = 0

fechada :: Poligonal -> Bool
fechada (p1:p2:[]) = (p1 == p2)
fechada (p1:p2:t) = fechada (p1:t)

triangula :: Poligonal -> [Figura]
triangula (p1:p2:p3:p4:t) = (Triangulo p1 p2 p3):triangula (p1:p3:p4:t)
triangula _ = []

--areaP :: Poligonal -> Double

--Exercício 3
data Contacto = Casa Integer
			  | Trab Integer
			  | Tlm Integer
			  | Email String
			  deriving Show

type Nome = String
type Agenda = [(Nome,[Contacto])]

acEmail :: Nome -> String -> Agenda -> Agenda --a
acEmail n e a = (n,[Email e]):a

verEmails :: Nome -> Agenda -> Maybe [String] --b
verEmails nome ( ( gajo , cont) :t) = if nome == gajo then Just (retira cont) else verEmails nome t
verEmails _ _ = Nothing

retira ( (Email x) :t) = x:retira t
retira (h:t) = retira t
retira _ = []

consTelefs :: [Contacto] -> [Integer] --c
consTelefs ((Casa x):t) = x:consTelefs t
consTelefs ((Trab x):t) = x:consTelefs t
consTelefs ((Tlm x):t) = x:consTelefs t
consTelefs (h:t) = consTelefs t
consTelefs _ = []

casa :: Nome -> Agenda -> Maybe Integer --d
casa nome ( ( gajo , cont ) :t) = if nome == gajo then Just (numCasa cont) else casa nome t
casa _ _ = Nothing

numCasa ( (Casa n):t ) = n
numCasa (h:t) = numCasa t
numCasa _ = 0

--Exercício 4
type Dia = Int
type Mes = Int
type Ano = Int

data Data = D Dia Mes Ano deriving Show

type TabDN = [(Nome,Data)]

procura :: Nome -> TabDN -> Maybe Data --a
procura nome ( ( gajo , dat ) :t) = if nome == gajo then Just dat else procura nome t
procura _ _ = Nothing

--idade :: Data -> Nome -> TabDN -> Maybe Int