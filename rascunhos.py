################## SUDOKU ##################

# n é o dado no enunciado

# adicionar nodos
for i in range(n^4):
	graph.add_node(i)

# ligar colunas
for i in range(n^4):
	for j in range(0,n^4,n^2):
		graph.add_edge(i,j)

# ligar linhas
casa = 1
while casa < n^4:
	for k in range(1,(n^2)-casa):
		graph.add_edge(casa, casa+k)
	casa += 1

1  2  3  | 4  5  6  | 7  8  9
10 11 12 | 13 14 15 | 16 17 18
19 20 21 | 22 23 24 | 25 26 27

111 112 113 | 121 122 123
114 115 116 | 124 125 126
117 118 119 | 127 128 129 