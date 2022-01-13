import ply.lex as lex
import sys

tokens = (
    'NUM',
    'NOME',
    'INT',
    'ARRAY',
    'MATRIZ',
    'SOMA',
    'SUB',
    'MULT',
    'DIV',
    'MOD',
    'MAIOR',
    'MENOR',
    'IGUAL',
    'MAIORI',
    'MENORI',
    'NIGUAL',
    'NEG',
    'E',
    'OU',
    'ATR',
    'LER',
    'ESCREVER',
    'SE',
    'ENTAO',
    'SENAO',
    'ENQUANTO',
    'FAZ',
    'FIM',
    'PCABRIR',
    'PCFECHAR',
    'PRABRIR',
    'PRFECHAR',
    'VIRG'
)

t_PCABRIR = r'\('
t_PCFECHAR = r'\)'
t_PRABRIR = r'\['
t_PRFECHAR = r'\]'
t_VIRG   = r','

def t_NUM(t):
    r'\d+'
    return t

def t_INT(t):
    r'int'
    return t

def t_ARRAY(t):
    r'array'
    return t

def t_MATRIZ(t):
    r'matriz'
    return t

def t_SOMA(t):
    r'soma'
    return t

def t_SUB(t):
    r'sub'
    return t

def t_MULT(t):
    r'mult'
    return t

def t_DIV(t):
    r'div'
    return t

def t_MOD(t):
    r'mod'
    return t

def t_MAIORI(t):
    r'maiori'
    return t

def t_MAIOR(t):
    r'maior'
    return t

def t_MENORI(t):
    r'menori'
    return t 

def t_MENOR(t):
    r'menor'
    return t

def t_IGUAL(t):
    r'igual'
    return t

def t_NIGUAL(t):
    r'nigual'
    return t

def t_NEG (t):
    r'neg'
    return t

def t_OU (t):
    r'ou'
    return t

def t_ATR (t):
    r'<-'
    return t

def t_LER (t):
    r'ler'
    return t

def t_ESCREVER (t):
    r'escrever'
    return t

def t_ENTAO(t):
    r'entao'
    return t

def t_SENAO(t):
    r'senao'
    return t 

def t_SE (t):
    r'se'
    return t

def t_ENQUANTO(t):
    r'enquanto'
    return t 

def t_FAZ(t):
    r'faz'
    return t 

def t_FIM(t):
    r'fim'
    return t

def t_E (t):
    r'e'
    return t

def t_NOME(t):
    r'\w+'
    return t

t_ignore = ' \r\t\n'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lexer = lex.lex() # cria um AnaLex especifico a partir da especificação acima usando o gerador 'lex' do objeto 'lex'
'''
# Reading input
for linha in sys.stdin:
    lexer.input(linha) 
    tok = lexer.token()
    while tok:
        print(tok)
        tok = lexer.token()'''