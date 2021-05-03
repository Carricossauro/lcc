'''

Implemente uma função que determina quantas permutações dos n primeiros digitos 
são múltiplas de um dado número d. Por exemplo se n for 3 temos as seguintes 
permutações: 123, 132, 213, 231, 312, 321. Se neste caso d for 3 então todas 
as 6 permutações são múltiplas.

multiplos(3,3)
6

multiplos(5,12)
24

'''

# Não é que é suposto fazer assim mas deu 13% lol
import itertools

def multiplos(n,d):
    return len(list(filter(lambda x: x % d == 0, list(map(lambda x: int("".join(map(str,x))),itertools.permutations([x for x in range(1,n+1)]))))))
