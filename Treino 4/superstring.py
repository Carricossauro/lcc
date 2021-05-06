'''

Implemente um função que calcula a menor string que contém todas as palavras 
recebidas na lista de input. Assuma que todas as palavras são disjuntas entre si, 
ou seja, nunca haverá inputs onde uma das palavras está contida noutra.

'''

from functools import reduce

def valid(strings, N, k, ls):
    return all(map(lambda x: x in ls, strings))

def extensions(strings, N, k, ls):
    return [x for x in strings if x not in ls]

def search(strings, N, k, ls, resList):
    string = reduce(lambda a,b: concat(a,b), ls)
    if len(string) == k:
        return valid(strings, N, k, ls)
    elif len(string) > k:
        return False
        
    for x in extensions(strings, N, k, ls):
        ls.append(x)
        if search(strings, N, k, ls, resList):
            string = reduce(lambda a,b: concat(a,b), ls)
            print(ls, k, string)
            resList.append(string)
            return True
        ls.pop()

    return False

def superstring(strings):
    res = "".join(strings)
    resList = [res]
    N = len(res)
    
    for k in range(1,N):
        if search(strings, N, k, [""], resList):
            return resList[-1]
    
    return resList[-1]

def concat(a, b):
    Na = len(a)
    Nb = len(b)
    k = 0
    x = Na
    
    for i in range(Na):
        k = i
        for j in range(Nb):
            if k == Na:
                break
            elif a[k] == b[j]:
                k+=1
            else:
                break
        if k == Na:
            x = i
            break
    
    return a[:x] + b
