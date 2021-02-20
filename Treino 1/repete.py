'''
Implemente uma função que determine qual a menor sequência de caracters que
contém n repetições de uma determinada palavra
'''

def repete(palavra,n):
    subStrings = []
    for i in range(1,len(palavra)):
        subStrings.append(palavra[i:])
            
    repeated=""
    for el in subStrings:
        if palavra[:len(el)] == el:
            repeated = el
            palavra = palavra[:-len(el)]
            break
    
    palavra = palavra*n + repeated*(n > 0)
    return palavra
