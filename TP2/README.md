# Declarar variaveis:

| Declaração                                      | Comando        |
| ----------------------------------------------- | -------------- |
| Criar inteiro "x"                               | INT x          |
| Criar inteiro "x" com valor v                   | INT x <- v     |
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

| IO                                | Comando    |
| --------------------------------- | ---------- |
| Ler do stdin                      | LER        |
| Escrever o valor de "x" no stdout | ESCREVER x |

# Controlo de fluxo:

Executar algo se "x" for verdadeiro

    SE (x) ENTAO
    ...
    FIM

Executar algo se "x" for verdadeiro, e outra coisa se "x" for falso

    SE (x) ENTAO
    ...
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

# GIC

        Programa : Corpo
        Programa : Decls Corpo
        Decls    : Decl
        Decls    : Decl Decls
        Decl     : INT NOME
        Decl     : INT NOME ATR NUM
        Decl     : ARRAY NOME NUM
        Decl     : MATRIZ NOME NUM NUM
        Corpo    : Proc
        Corpo    : Proc Corpo
        Proc     : Atrib
        Proc     : Se
        Proc     : Escrever
        Proc     : Enquanto
        Atrib    : NOME ATR Expr
        Atrib    : NOME ATR LER
        Se       : SE Cond ENTAO Corpo FIM
        Se       : SE Cond ENTAO Corpo SENAO Corpo FIM
        Enquanto : ENQUANTO Cond FAZ Corpo FIM
        Escrever : ESCREVER Expr
        Expr     : NOME PRABRIR Var PRFECHAR
        Expr     : NOME PRABRIR Var VIRG Var PRFECHAR
        Expr     : Var
        Expr     : Cond
        Expr     : SOMA PCABRIR Expr VIRG Expr PCFECHAR
        Expr     : SUB PCABRIR Expr VIRG Expr PCFECHAR
        Expr     : MULT PCABRIR Expr VIRG Expr PCFECHAR
        Expr     : DIV PCABRIR Expr VIRG Expr PCFECHAR
        Expr     : MOD PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : MAIOR PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : MENOR PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : MAIORI PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : MENORI PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : IGUAL PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : NIGUAL PCABRIR Expr VIRG Expr PCFECHAR
        Cond     : E PCABRIR Cond VIRG Cond PCFECHAR
        Cond     : OU PCABRIR Cond VIRG Cond PCFECHAR
        Cond     : NEG PCABRIR Cond PCFECHAR
        Var      : NOME
        Var      : NUM

# Testes

| Ficheiro       | Exemplo                                                                      |
| -------------- | ---------------------------------------------------------------------------- |
| quadrado.txt   | ler 4 números e dizer se podem ser os lados de um quadrado                   |
| menor.txt      | ler um inteiro N, depois ler N números e escrever o menor deles              |
| produtorio.txt | ler N (constante do programa) números e calcular e imprimir o seu produtório |
| impares.txt    | contar e imprimir os números impares de uma sequência de números naturais    |
| array.txt      | ler e armazenar N números num array; imprimir os valores por ordem inversa   |
| matriz.txt     | ler e armazenar N números numa matriz; imprimir a soma de cada linha         |
