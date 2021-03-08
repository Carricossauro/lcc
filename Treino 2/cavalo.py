'''

O objectivo deste problema é determinar quantos movimentos são necessários para 
movimentar um cavalo num tabuleiro de xadrez entre duas posições.
A função recebe dois pares de coordenadas, que identificam a origem e destino pretendido,
devendo devolver o número mínimo de saltos necessários para atingir o destino a partir da origem.
Assuma que o tabuleiro tem tamanho ilimitado.

'''

def movimentos(x, y, m):
    movs = []
    
    # Cima
    movs.append(((x+1,y+2), m+1))
    movs.append(((x-1,y+2), m+1))
    # Baixo
    movs.append(((x+1,y-2), m+1))
    movs.append(((x-1,y-2), m+1))
    # Direita
    movs.append(((x+2,y-1), m+1))
    movs.append(((x+2,y+1), m+1))
    # Esquerda
    movs.append(((x-2,y-1), m+1))
    movs.append(((x-2,y+1), m+1))
    
    return movs

def saltos(o,d):
    orla = [(o,0)]
    
    for pos, mov in orla:
        if pos == d:
            return mov
            
        orla += movimentos(pos[0], pos[1], mov)
    
    return (o,0)
