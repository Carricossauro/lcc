# frequencia.py
def frequencia(texto):
    palavras = texto.split()
    dicionario = {}
    
    for pal in palavras:
        if pal not in dicionario:
            dicionario[pal] = 0
        dicionario[pal] -= 1
    
    palavras = set(palavras)
    palavras = list(palavras)
    palavras.sort(key=lambda x: (dicionario[x],x))
    return palavras
