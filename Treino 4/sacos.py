'''

Os sacos de um supermercado tem um limite de peso que conseguem levar. 
Implemente uma função que o ajude a determinar o número mínimo de sacos que 
necessita para levar todas as compras. A função recebe o peso máximo que os
sacos conseguem levar e uma lista com os pesos de todos os items que pretende 
comprar. Deverá devolver o número mínimo de sacos que necessita para levar 
todas as compras.

'''

# 10%
def extensions(peso, compras, k, i, sacos):
    return [x for x in range(k) if sacos[x] + compras[i] <= peso]

def search(peso, compras, N, k, i, sacos):
    if N == i:
        return True

    for x in extensions(peso, compras, k, i, sacos):
        sacos[x] += compras[i]
        if search(peso, compras, N, k, i+1, sacos):
            return True
        sacos[x] -= compras[i]

    return False

def sacos(peso,compras):
    N = len(compras)

    for k in range(1, len(compras)):
        sacos = [0 for _ in range(k)]
        if search(peso, compras, N, k, 0, sacos):
            return k

    return N
