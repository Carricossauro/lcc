'''

Implemente uma função que calcula a área de um mapa que é acessível por
um robot a partir de um determinado ponto.
O mapa é quadrado e representado por uma lista de strings, onde um '.' representa
um espaço vazio e um '*' um obstáculo.
O ponto inicial consistirá nas coordenadas horizontal e vertical, medidas a 
partir do canto superior esquerdo.
O robot só consegue movimentar-se na horizontal ou na vertical. 

'''
def visitaveis(pos, visitado, mapa, n):
    orla = []
    # Cima
    for i in range(pos[1]-1, -1, -1):
        if mapa[i][pos[0]] != '.':
            break
        elif not visitado[i][pos[0]]:
            orla.append((pos[0],i))
            
    # Baixo
    for i in range(pos[1]+1, n):
        if mapa[i][pos[0]] != '.':
            break
        elif not visitado[i][pos[0]]:
            orla.append((pos[0],i))
            
    # Esquerda
    for i in range(pos[0]-1, -1, -1):
        if mapa[pos[1]][i] != '.':
            break
        elif not visitado[pos[1]][i]:
            orla.append((i,pos[1]))
            
    # Direita
    for i in range(pos[0]+1, n):
        if mapa[pos[1]][i] != '.':
            break
        elif not visitado[pos[1]][i]:
            orla.append((i,pos[1]))
            
    return orla

def area(p,mapa):
    n = len(mapa)
    visitado = [[False]*n for _ in range(n)]
    acessivel = 0
    x = 0
    orla = [p]
    
    while len(orla) != x:
        pos = orla[x]
        if not visitado[pos[1]][pos[0]]:
            acessivel += 1
        
        x += 1
        visitado[pos[1]][pos[0]] = True
        
        orla += visitaveis(pos, visitado, mapa,n)
    
    return acessivel