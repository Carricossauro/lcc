'''

Implemente uma função que descubra o maior conjunto de pessoas que se conhece 
mutuamente. A função recebe receber uma sequências de pares de pessoas que se 
conhecem e deverá devolver o tamanho do maior conjunto de pessoas em que todos 
conhecem todos os outros.

conhecidos = {('pedro','maria'),('pedro','jose'),('pedro','manuel'),('maria','jose'),('maria','francisca'),('jose','francisca'),('francisca','manuel')}
amigos(conhecidos) -> 3
            
conhecidos = {('pedro','maria'),('jose','francisca'),('manuel','pedro')}
amigos(conhecidos) -> 2

'''

# 9%
def complete(n, ls):
    return n == len(ls)

def existeAresta(conhecidos, a, b):
    return any(map(lambda tup: a in tup and b in tup, conhecidos))

def extensions(n, ls, amigos, conhecidos):
    return [x for x in amigos if all(map(lambda y: y != x and existeAresta(conhecidos, x, y), ls))]

def search(n, ls, conhecidos, amigos):
    if complete(n, ls):
        return True
    for x in extensions(n, ls, amigos, conhecidos):
        ls.append(x)
        if search(n, ls, conhecidos, amigos):
            return True
        ls.pop()
    return False

def amigos(conhecidos):
    amigos = set([a for tup in conhecidos for a in tup])
    for n in range(len(amigos)-1,2, -1):
        ls = []
        if search(n, ls, conhecidos, amigos):
            return n
    return 2
