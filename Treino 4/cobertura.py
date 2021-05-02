'''

Implemente uma função que calcula o número mínimo de nós de um grafo 
não orientado que cobrem todas as arestas, ou seja, o tamanho do menor 
conjunto de nós que contém pelo menos um extremo de cada aresta. 
A função recebe a lista de todas as arestas do grafo, sendo cada aresta um 
par de nós.

arestas = [('portugal','espanha'),('espanha','franca'),('franca','alemanha'),('alemanha','belgica'),('belgica','franca'),('usa','canada'),('usa','mexico'),('marrocos','argelia'),('argelia','libia'),('argelia','mali')]
5

arestas = [('a','b'),('b','c'),('c','d'),('d','e'),('e','f'),('f','g'),('g','h')]
4
            
'''

# 9%
def extensions(nos, ls):
    return [x for x in nos if x not in ls]

def complete(ls, n):
    return len(ls) == n
    
def valid(ls, n, arestas):
    return all(map(lambda tup: tup[0] in ls or tup[1] in ls, arestas))

def search(nos, ls, n, arestas):
    if complete(ls, n):
        return valid(ls, n, arestas)
    for x in extensions(nos, ls):
        ls.append(x)
        if search(nos, ls, n, arestas):
            return True
        ls.pop()
    return False

def cobertura(arestas):
    nos = set([i for tup in arestas for i in tup])
    if len(arestas) == 0:
        return 0
    for i in range(1,len(nos)):
        c = []
        if search(nos, c, i, arestas):
            return i
    return len(nos)
