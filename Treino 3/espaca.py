"""

Implemente uma função que, dada uma frase cujos espaços foram retirados, 
tenta recuperar a dita frase. Para além da frase (sem espaços nem pontuação), 
a função recebe uma lista de palavras válidas a considerar na reconstrução 
da dita frase. Deverá devolver a maior frase que pode construir inserindo
espaços na string de entrada e usando apenas as palavras que foram indicadas 
como válidas. Por maior entende-se a que recupera o maior prefixo da string
de entrada. Só serão usados testes em que a maior frase é única.


"""

# Programação Dinâmica - 10%
def espaca(frase,palavras):
    n = len(frase)
    cache = ["" for x in range(n+1)]
    
    for x in range(n+1):
        for y in range(n+1):
            if x == 0:
                cache[y] = ""
            else:
                pal = frase[x-1:y]
                if pal in palavras:
                    ant = cache[x-1]
                    cache[y] = ant + " "*(ant != "") + pal if cache[y] == "" else cache[y]

    return cache[n]
