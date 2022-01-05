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

def t_NOME(t):
    r'[a-z]+'
    return t

def t_INT(t):
    r'INT'
    return t

def t_ARRAY(t):
    r'ARRAY'
    return t

def t_MATRIZ(t):
    r'MATRIZ'
    return r

def t_SOMA(t):
    r'SOMA'
    return t

def t_SUB(t):
    r'SUB'
    return t

def t_MULT(t):
    r'MULT'
    return t

def t_DIV(t):
    r'DIV'
    return t

def t_MOD(t):
    r'MOD'
    return t

def t_MAIOR(t):
    r'MAIOR'
    return t

def t_MENOR(t):
    r'MENOR'
    return t

def t_IGUAL(t):
    r'IGUAL'
    return t

def t_MAIORI(t):
    r'MAIORI'
    return t

def t_MENORI(t):
    r'MENORI'
    return t 

def t_NIGUAL(t):
    r'NIGUAL'
    return t

def t_NEG (t):
    r'NEG'
    return t

def t_OU (t):
    r'OU'
    return t

def t_ATR (t):
    r'<-'
    return t

def t_LER (t):
    r'LER'
    return t

def t_ESCREVER (t):
    r'ESCREVER'
    return t

def t_SE (t):
    r'SE'
    return t

def t_ENTAO(t):
    r'ENTAO'
    return t

def t_SENAO(t):
    r'SENAO'
    return t 

def t_ENQUANTO(t):
    r'ENQUANTO'
    return t 

def t_FAZ(t):
    r'FAZ'
    return t 

def t_FIM(t):
    r'FIM'
    return t

def t_E (t):
    r'E'
    return t

t_ignore = ' \r\t\n'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)
 
lexer = lex.lex() # cria um AnaLex especifico a partir da especificação acima usando o gerador 'lex' do objeto 'lex'

# Reading input
for linha in sys.stdin:
    lexer.input(linha) 
    tok = lexer.token()
    while tok:
        print(tok)
        tok = lexer.token()