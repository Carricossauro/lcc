# apelidos.py
def apelidos(nomes):
    result = []
    for pessoa in nomes:
        quantidade = len(pessoa.split())
        posicao = 0
        for nome in result:
            quant = len(nome.split())
            if quantidade == quant:
                if nome > pessoa:
                    break
            elif quantidade > quant:
                break
            posicao += 1
        result.insert(posicao, pessoa)
    return result
