# apelidos.py
def apelidos(nomes):
    nomes.sort(key=lambda x: (len(x.split()),x))
    return nomes
