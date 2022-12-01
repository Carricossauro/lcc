# Declarar variaveis:

| Declaração                                      | Comando        |
| ----------------------------------------------- | -------------- |
| Criar inteiro "x"                               | int x          |
| Criar inteiro "x" com valor v                   | int x <- v     |
| Criar array de inteiros "a" de tamanho t        | array a t      |
| Criar matriz de inteiros "m" de tamanho t1 X t2 | matriz m t1 t2 |

# Operações aritméticas:

| Operação                                         | Comando     |
| ------------------------------------------------ | ----------- |
| Somar "x" e "y"                                  | soma (x, y) |
| Subtrair "y" a "x"                               | sub (x, y)  |
| Multiplicar "x" por "y"                          | mult (x, y) |
| Dividir "x" por "y"                              | div (x, y)  |
| Calcular resto da divisao inteira de "x" por "y" | mod (x, y)  |

# Operações Relacionais:

| Operação | Comando       |
| -------- | ------------- |
| x > y    | maior (x, y)  |
| x < y    | menor (x, y)  |
| x == y   | igual (x, y)  |
| x >= y   | maiori (x, y) |
| x <= y   | menori (x, y) |
| x != y   | nigual (x, y) |

# Operações Lógicas:

| Operação                 | Comando   |
| ------------------------ | --------- |
| Negar "x"                | neg (x)   |
| Conjunção de "x" com "y" | e (x, y)  |
| Disjunção de "x" e "y"   | ou (x, y) |

# Atribuição:

| Atribuição                      | Comando |
| ------------------------------- | ------- |
| Atribuir a "x" o valor de "y"   | x <- y  |
| Atribuir a "x" um valor inteiro | x <- 5  |

# IO:

| IO                                | Comando    |
| --------------------------------- | ---------- |
| Ler do stdin                      | ler        |
| Escrever o valor de "x" no stdout | escrever x |

# Controlo de fluxo:

Executar algo se "x" for verdadeiro

    se (x) entao
    ...
    fim

Executar algo se "x" for verdadeiro, e outra coisa se "x" for falso

    se (x) entao
    ...
    senao
    ...
    fim

# Ciclos:

Ciclo while-do

    enquanto (x) faz
    ...
    fim

# Indexação: (i, j inteiros)

Aceder indice "i" de um array

    array[i]

Aceder indice "i","j" de uma matriz (matrix[ i ][ j ] em C)

    matriz[i,j]

# GIC

    Programa : Corpo
             | Decls Corpo
    Decls    : Decl
             | Decls Decl
    Decl     : INT NOME
             | INT NOME ATR NUM
             | ARRAY NOME NUM
             | MATRIZ NOME NUM NUM
    Corpo    : Proc
             | Corpo Proc
    Proc     : Atrib
             | Se
             | Escrever
             | Enquanto
    Se       : SE Cond ENTAO Corpo FIM
             | SE Cond ENTAO Corpo SENAO Corpo FIM
    Enquanto : ENQUANTO Cond FAZ Corpo FIM
    Atrib    : NOME ATR Expr
             | NOME PRABRIR Expr PRFECHAR ATR Expr
             | NOME PRABRIR Expr VIRG Expr PRFECHAR ATR Expr
             | NOME PRABRIR Expr PRFECHAR ATR LER
             | NOME PRABRIR Expr VIRG Expr PRFECHAR ATR LER
             | NOME ATR LER
    Escrever : ESCREVERA NOME
             | ESCREVER Expr
    Expr     : PCABRIR Expr PCFECHAR
             | Var
             | Num
             | SOMA PCABRIR Expr VIRG Expr PCFECHAR
             | SUB PCABRIR Expr VIRG Expr PCFECHAR
             | MULT PCABRIR Expr VIRG Expr PCFECHAR
             | DIV PCABRIR Expr VIRG Expr PCFECHAR
             | MOD PCABRIR Expr VIRG Expr PCFECHAR
             | Cond
    Cond     : PCABRIR Cond PCFECHAR
             | MAIOR PCABRIR Expr VIRG Expr PCFECHAR
             | MENOR PCABRIR Expr VIRG Expr PCFECHAR
             | MAIORI PCABRIR Expr VIRG Expr PCFECHAR
             | MENORI PCABRIR Expr VIRG Expr PCFECHAR
             | IGUAL PCABRIR Expr VIRG Expr PCFECHAR
             | NIGUAL PCABRIR Expr VIRG Expr PCFECHAR
             | E PCABRIR Cond VIRG Cond PCFECHAR
             | OU PCABRIR Cond VIRG Cond PCFECHAR
             | NEG PCABRIR Cond PCFECHAR
    Var      : NOME PRABRIR Expr VIRG Expr PRFECHAR
             | NOME PRABRIR Expr PRFECHAR
             | NOME

# Testes

| Ficheiro         | Exemplo                                                                             |
| ---------------- | ----------------------------------------------------------------------------------- |
| quadrado.txt     | ler 4 números e dizer se podem ser os lados de um quadrado                          |
| menor.txt        | ler um inteiro N, depois ler N números e escrever o menor deles                     |
| produtorio.txt   | ler N (constante do programa) números e calcular e imprimir o seu produtório        |
| impares.txt      | contar e imprimir os números impares de uma sequência de números naturais           |
| array.txt        | ler e armazenar N números num array; imprimir os valores por ordem inversa          |
| matriz.txt       | ler e armazenar N números numa matriz; imprimir a soma de cada linha                |
| ordenarArray.txt | ler e armazenar N números num array; ordenar o array; imprimir os valores ordenados |
