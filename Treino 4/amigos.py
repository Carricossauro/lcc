'''

Implemente uma função que descubra o maior conjunto de pessoas que se conhece 
mutuamente. A função recebe receber uma sequências de pares de pessoas que se 
conhecem e deverá devolver o tamanho do maior conjunto de pessoas em que todos 
conhecem todos os outros.

'''

def complete(n, ls):
    return n == len(ls)

def existeAresta(adj, a, b):
    return a in adj[b]

def extensions(n, ls, amigos, adj):
    return [x for x in amigos if all(map(lambda y: y != x and existeAresta(adj, x, y), ls))]

def search(n, ls, adj, amigos):
    if complete(n, ls):
        return True
    for x in extensions(n, ls, amigos, adj):
        ls.append(x)
        if search(n, ls, adj, amigos):
            return True
        ls.pop()
    return False

def amigos(conhecidos):
    amigos = set([a for tup in conhecidos for a in tup])
    adj = {}
    
    if len(conhecidos) == 0:
        return 0
    
    for x in amigos:
        adj[x] = set()
    for tup in conhecidos:
        adj[tup[0]].add(tup[1])
        adj[tup[1]].add(tup[0])
    
    for n in range(len(amigos),2, -1):
        ls = []
        if search(n, ls, adj, amigos):
            return n
    return 2
