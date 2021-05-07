'''

Implemente uma função que calcula o número mínimo de nós de um grafo 
não orientado que cobrem todas as arestas, ou seja, o tamanho do menor 
conjunto de nós que contém pelo menos um extremo de cada aresta. 
A função recebe a lista de todas as arestas do grafo, sendo cada aresta um 
par de nós.

'''

# 10%
def extensions(vertices, ls, k):
    return [x for x in range(k, len(vertices)) if  x not in ls]

def valid(ls, n, arestas):
    return all(map(lambda tup: tup[0] in ls or tup[1] in ls, arestas))

def search(vertices, ls, n, arestas, tam, total):
    if n == tam:
        return valid(ls, n, arestas)
    elif total + len(ls) - tam < n:
        return False

    for x in extensions(vertices, ls, tam):
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
        c = [""]
        if search(vertices, c, i, novasArestas, 0, N):
            return i

    return N
