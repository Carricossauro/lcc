'''

Implemente uma função que descubra o maior conjunto de pessoas que se conhece
mutuamente. A função recebe receber uma sequências de pares de pessoas que se
conhecem e deverá devolver o tamanho do maior conjunto de pessoas em que todos
conhecem todos os outros.

'''

# 10%
def extensions(ls, k, total, n):
    return [x for x in range(k, total) if x not in ls and total - x + k >= n]

def valid(ls, n, arestas, incluido):
    return all(map(lambda tup: incluido[tup[0]] or incluido[tup[1]], arestas))

def search(ls, n, arestas, tam, total, incluido):
    if n == tam:
        return valid(ls, n, arestas, incluido)
    #elif total - ls[-1] - 1 + tam < n: # Esta condição não executa se as extensões estiverem bem feitas
    #    return False

    for x in extensions(ls, tam, total, n):
        ls.append(x)
        incluido[x] = True
        if search(ls, n, arestas, tam+1, total, incluido):
            return True
        incluido[x] = False
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
        
    incluido = [False for x in range(N)]

    for i in range(1,N):
        c = [-1]
        if search(c, i, novasArestas, 0, N, incluido):
            return i

    return N
