'''

Implemente uma função que calcula o número mínimo de nós de um grafo 
não orientado que cobrem todas as arestas, ou seja, o tamanho do menor 
conjunto de nós que contém pelo menos um extremo de cada aresta. 
A função recebe a lista de todas as arestas do grafo, sendo cada aresta um 
par de nós.

'''

# 10%
def extensions(vertices, ls, k, total, n):
    return [x for x in range(k, len(vertices)) if x not in ls and total - x + k >= n]

def valid(ls, n, arestas):
    return all(map(lambda tup: tup[0] in ls or tup[1] in ls, arestas))

def search(vertices, ls, n, arestas, tam, total):
    if n == tam:
        return valid(ls, n, arestas)
    elif total - ls[-1] - 1 + tam < n: # Esta condição não executa se as extensões estiverem bem feitas
        return False

    for x in extensions(vertices, ls, tam, total, n):
        ls.append(x)
        if search(vertices, ls, n, arestas, tam+1, total):
            return True
        ls.pop()

    return False

def cobertura(arestas):
    vertices = list(set([i for tup in arestas for i in tup]))

    if len(arestas) == 0:
        return 0

    N = len(vertices)
    novasArestas = []
    for a,b in arestas:
        novasArestas.append( (vertices.index(a), vertices.index(b)) )

    for i in range(1,N):
        c = [-1]
        if search(vertices, c, i, novasArestas, 0, N):
            return i

    return N
