'''

Implemente uma função que dada uma lista de conjuntos de inteiros determine qual
o menor número desses conjuntos cuja união é idêntica à união de todos os 
conjuntos recebidos.

sets = [{1,2,3},{2,4},{3,4},{4,5}]
self.assertEqual(uniao(sets),2)

sets = [{1},{2},{3,4},{5,6,7,8},{1,3,5,7},{2,4,6,8},{9}]
self.assertEqual(uniao(sets),3)

'''

# 10%
def complete(sets, ls, un, x):
    return x == len(ls)

def valid(sets, ls, un, x):
    resp = set()
    for y in ls:
        resp = resp.union(sets[y])
    return un == resp

def extensions(sets, ls, un, x):
    lista = []
    for i in range(len(sets)):
        if i not in ls:
            lista.append(i)
    return lista

def search(sets, ls, un, x):
    if complete(sets, ls, un, x):
        return valid(sets, ls, un, x)

    for k in extensions(sets, ls, un, x):
        ls.append(k)
        if search(sets, ls, un, x):
            return True
        ls.pop()

    return False

def uniao(sets):
    N = len(sets)
    un = set()
    for x in sets:
        un = un.union(x)

    for x in range(N):
        ls = []
        if search(sets, ls, un, x):
            return x

    return N
