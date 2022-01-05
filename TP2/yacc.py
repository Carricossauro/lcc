import ply.yacc as yacc
import sys

from lex import tokens

# inicio da GIC

def p_lisp_grammar(p):
    """
        Programa : Decls Corpo
        Decls    : Decl Decls
        Decl     : INT NOME
        Decl     : ARRAY NOME NUM
        Decl     : MATRIZ NOME NUM NUM
        Corpo    : Proc Corpo
        Proc     : Atrib
        Proc     : Se
        Proc     : Escrever
        Proc     : Enquanto
        Atrib    : NOME ATR Expr
        Atrib    : NOME ATR LER
        Se       : SE Cond ENTAO Corpo FIM
        Se       : SE Cond ENTAO Corpo FIM SENAO Corpo FIM
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
    """