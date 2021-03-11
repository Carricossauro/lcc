'''

Podemos usar um (multi) grafo para representar um mapa de uma cidade: 
cada nó representa um cruzamento e cada aresta uma rua.
Pretende-se que implemente uma função que calcula o tamanho de uma cidade, 
sendo esse tamanho a distância entre os seus cruzamentos mais afastados.
A entrada consistirá numa lista de nomes de ruas (podendo assumir que os 
nomes de ruas são únicos). Os identificadores dos cruzamentos correspondem a 
letras do alfabeto, e cada rua começa (e acaba) no cruzamento 
identificado pelo primeiro (e último) caracter do respectivo nome.


> ruas = ["raio","central","liberdade","chaos","saovictor","saovicente","saodomingos","souto","capelistas","anjo","taxa"]
> 25


> ruas = ["ab","bc","bd","cd"]
> 4

'''
###################################################################################
# Isto falha num teste dos 5, vou tentar usar alguma coisa mais eificiente depois #
###################################################################################
def caminhos(ruas, origem):
    res = {origem:0}
    orla = [(origem,0, [])]
    
    while orla:
        dest, tam, hist = orla.pop(0)
        for rua in ruas:
            if dest in rua:
                if dest == rua[0]:
                    prox = rua[1]
                else:
                    prox = rua[0]
                if prox in hist:
                    continue
                novaDist = rua[2] + tam
                
                if prox not in res:
                    res[prox] = novaDist
                    orla.append( (prox, novaDist, hist + [dest]) )
                elif res[prox] > novaDist:
                    res[prox] = novaDist
                    orla.append( (prox, novaDist, hist + [dest]) )
    
    return res

def fixRuas(ruas):
    final = []
    for rua in ruas:
        if rua[0] != rua[-1]:
            final.append( (rua[0], rua[-1], len(rua)) )
    return final

def tamanho(ruas):
    ruas = fixRuas(ruas)
    final = {}
    vertices = set(list(map(lambda x: x[0], ruas)) + list(map(lambda x: x[1], ruas)))
    m = -1
    
    for x in vertices:
        final[x] = caminhos(ruas, x)
        for _,y in final[x].items():
            m = max(y,m)
    
    return m
