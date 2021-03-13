'''

O objectivo deste problema é determinar quantos movimentos são necessários para 
movimentar um cavalo num tabuleiro de xadrez entre duas posições.
A função recebe dois pares de coordenadas, que identificam a origem e destino pretendido,
devendo devolver o número mínimo de saltos necessários para atingir o destino a partir da origem.
Assuma que o tabuleiro tem tamanho ilimitado.

'''

def movimentos(x, y, m, movs):
    dx = [1,-1,1,-1,2,2,-2,-2]
    dy = [2,2,-2,-2,-1,1,-1,1]
    
    for i in range(8):
        newX = x + dx[i]
        newY = y + dy[i]
        
        movs.append( ((newX,newY), m+1) )
    
    return movs

def saltos(o,d):
    orla = [(o,0)]
    
    while orla:
        pos,mov = orla.pop(0)
        if pos == d:
            return mov
            
        movimentos(pos[0], pos[1], mov, orla)
    
    return 0
