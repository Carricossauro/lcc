"""

Implemente uma função que determina qual a probabilidade de um robot regressar 
ao ponto de partida num determinado número de passos. Sempre que o robot dá um 
passo tem uma determinada probabilidade de seguir para cima ('U'), baixo ('D'), 
esquerda ('L') ou direita ('R'). A função recebe o número de passos que o 
robot vai dar e um dicionário com probabilidades de se movimentar em cada uma
das direcções (as chaves são os caracteres indicados entre parêntesis).
O resultado deve ser devolvido com a precisao de 2 casas decimais.

"""

# Programação Dinâmica - 10%
def probabilidade(passos,probabilidade):
    probs = [{} for x in range(passos+1)]
    
    for k in range(2):
        for x in range(-passos, passos+1):
            for y in range(passos+1):
                probs[0][(x,y)] = 0.0
            for y in range(-passos,0):
                probs[0][(x,y)] = 0.0
    
    probs[0][(0,0)] = 1.0
    lado = ['L', 'R', 'U', 'D']
    dx = [-1,1,0, 0]
    dy = [ 0,0,1,-1]

    for p in range(1, passos+1):
        for x in range(-passos, passos+1):
            for y in range(-passos, passos+1):
                if (x,y,p) == (0,0,0):
                    probs[p][(x,y)] = 1.0
                else:
                    probs[p][(x,y)] = 0.0
                    for k2 in range(4):
                        X = x + dx[k2]
                        Y = y + dy[k2]
                        if -passos < X < passos and -passos < Y < passos:
                            antiga = probabilidade[lado[k2]]*probs[p-1][(X,Y)]
                            probs[p][(x,y)] += antiga
    
    return round(probs[passos][(0,0)],2)
