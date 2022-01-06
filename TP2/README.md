# Declarar variaveis:

| Declaração                                      | Comando        |
| ----------------------------------------------- | -------------- |
| Criar inteiro "x"                               | INT x          |
| Criar array de inteiros "a" de tamanho t        | ARRAY a t      |
| Criar matriz de inteiros "m" de tamanho t1 X t2 | MATRIZ m t1 t2 |

# Operações aritméticas:

| Operação                                         | Comando     |
| ------------------------------------------------ | ----------- |
| Somar "x" e "y"                                  | SOMA (x, y) |
| Subtrair "y" a "x"                               | SUB (x, y)  |
| Multiplicar "x" por "y"                          | MULT (x, y) |
| Dividir "x" por "y"                              | DIV (x, y)  |
| Calcular resto da divisao inteira de "x" por "y" | MOD (x, y)  |

# Operações Relacionais:

| Operação | Comando       |
| -------- | ------------- |
| x > y    | MAIOR (x, y)  |
| x < y    | MENOR (x, y)  |
| x == y   | IGUAL (x, y)  |
| x >= y   | MAIORI (x, y) |
| x <= y   | MENORI (x, y) |
| x != y   | NIGUAL (x, y) |

# Operações Lógicas:

| Operação                 | Comando   |
| ------------------------ | --------- |
| Negar "x"                | NEG (x)   |
| Conjunção de "x" com "y" | E (x, y)  |
| Disjunção de "x" e "y"   | OU (x, y) |

# Atribuição:

| Atribuição                      | Comando |
| ------------------------------- | ------- |
| Atribuir a "x" o valor de "y"   | x <- y  |
| Atribuir a "x" um valor inteiro | x <- 5  |

# IO:

| IO                 | Comando  |
| ------------------ | -------- |
| Ler do stdin       | LER      |
| Escrever no stdout | ESCREVER |

# Controlo de fluxo:

Executar algo se "x" for verdadeiro, e outra coisa se "x" for falso

    SE (x) ENTAO
    ...
    FIM
    SENAO
    ...
    FIM

# Ciclos:

Ciclo while-do

    ENQUANTO (x) FAZ
    ...
    FIM

# Indexação: (i, j inteiros)

Aceder indice "i" de um array

    array[i]

Aceder indice "i","j" de uma matriz (matrix[ i ][ j ] em C)

    matriz[i,j]
