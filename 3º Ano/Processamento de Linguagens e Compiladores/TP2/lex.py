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
    'VIRG',
    'ESCREVERA'
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
    r'(?i:int)'
    return t

def t_ARRAY(t):
    r'(?i:array)'
    return t

def t_MATRIZ(t):
    r'(?i:matriz)'
    return t

def t_SOMA(t):
    r'(?i:soma)'
    return t

def t_SUB(t):
    r'(?i:sub)'
    return t

def t_MULT(t):
    r'(?i:mult)'
    return t

def t_DIV(t):
    r'(?i:div)'
    return t

def t_MOD(t):
    r'(?i:mod)'
    return t

def t_MAIORI(t):
    r'(?i:maiori)'
    return t

def t_MAIOR(t):
    r'(?i:maior)'
    return t

def t_MENORI(t):
    r'(?i:menori)'
    return t 

def t_MENOR(t):
    r'(?i:menor)'
    return t

def t_IGUAL(t):
    r'(?i:igual)'
    return t

def t_NIGUAL(t):
    r'(?i:nigual)'
    return t

def t_NEG (t):
    r'(?i:neg)'
    return t

def t_OU (t):
    r'(?i:ou)'
    return t

def t_ATR (t):
    r'<-'
    return t

def t_LER (t):
    r'(?i:ler)'
    return t

def t_ESCREVERA(t):
    r'(?i:escrevera)'
    return t

def t_ESCREVER (t):
    r'(?i:escrever)'
    return t

def t_ENTAO(t):
    r'(?i:entao)'
    return t

def t_SENAO(t):
    r'(?i:senao)'
    return t 

def t_SE (t):
    r'(?i:se)'
    return t

def t_ENQUANTO(t):
    r'(?i:enquanto)'
    return t 

def t_FAZ(t):
    r'(?i:faz)'
    return t 

def t_FIM(t):
    r'(?i:fim)'
    return t

def t_E (t):
    r'(?i:e)'
    return t

def t_NOME(t):
    r'[a-z]\w*'
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
