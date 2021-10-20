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