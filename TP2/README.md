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
