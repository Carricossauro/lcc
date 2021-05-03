'''

Um ciclo Hamiltoniano num grafo não orientado é um caminho no grafo que passa
uma e uma só vez por cada nó e termina no nó onde começou.

Implemente uma função que calcula o menor (em ordem lexicográfica) ciclo 
Hamiltoniano de um grafo, caso exista. Se não existir deve devolver None.

arestas = [(0,1),(1,2),(0,3),(1,3),(1,4),(2,4),(3,4)]
[0,1,2,4,3]

arestas = [(0,1),(1,2),(0,3),(1,3),(1,4),(2,4)]
None

'''

# 11%
def extensions(N, verts, arestas, ls):
    lista = set()
    x = ls[-1]
    
    for a,b in arestas:
        if x == a and b not in ls:
            lista.add(b)
        if x == b and a not in ls:
            lista.add(a)

    return lista

def complete(N, verts, arestas, ls):
    return len(ls) == N

def valid(arestas, ls):
    return any(map(lambda tup: ls[0] in tup and ls[-1] in tup,arestas))

def search(N, verts, arestas, ls):
    if complete(N, verts, arestas, ls):
        return valid(arestas, ls)
    
    for x in extensions(N, verts, arestas, ls):
        ls.append(x)
        if search(N, verts, arestas, ls):
            return True
        ls.pop()
        
    return False

def hamilton(arestas):
    verts = set([x for tup in arestas for x in tup])
    n = len(verts)
    
    for x in verts:
        ls = [x]
        if search(n, verts, arestas, ls):
            return ls

    return None
