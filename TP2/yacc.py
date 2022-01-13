import ply.yacc as yacc
import sys

from lex import tokens

def p_Programa(p):
    "Programa : Corpo"
    print("START")
    print(p[1], end="")
    print("STOP")

def p_Programa(p):
    "Programa : Decls Corpo"
    print(p[1], end="")
    print("START")
    print(p[2], end="")
    print("STOP")

def p_Decls(p):
    "Decls    : Decl"
    p[0] = f'{p[1]}'

def p_Decls_Recursiva(p):
    "Decls    : Decl Decls"
    p[0] = f'{p[1]}{p[2]}'

def p_Decl_Int(p):
    "Decl     : INT NOME"
    if p[2] not in p.parser.registers:
        p.parser.registers.update({p[2] : p.parser.gp})
        p[0] = f'PUSHI 0\n'
        p.parser.ints.append(p[2])
        p.parser.gp += 1
    else:
        print("Erro: Variável já existe")
        parser.success = False

def p_Decl_Int_Atr(p):
    "Decl     : INT NOME ATR NUM"
    if p[2] not in p.parser.registers:
        p.parser.registers.update({p[2] : p.parser.gp})
        p[0] = f'PUSHI {p[4]}\n'
        p.parser.ints.append(p[2])
        p.parser.gp += 1
    else:
        print("Erro: Variável já existe")
        parser.success = False

def p_Decl_Array(p):
    "Decl     : ARRAY NOME NUM"
    if p[2] not in p.parser.registers:
        p.parser.registers.update({p[2] : p.parser.gp})
        p[0] = f'PUSHN {p[3]}\n'
        p.parser.gp += int(p[3])
    else:
        print("Erro: Variável já existe")
        parser.success = False

def p_Decl_Matriz(p):
    "Decl     : MATRIZ NOME NUM NUM"
    if p[2] not in p.parser.registers:
        p.parser.registers.update({p[2] : (p.parser.gp, int(p[3]), int(p[4]))})
        size = int(p[3])*int(p[4])
        p[0] = f'PUSHN {str(size)}\n'
        p.parser.gp += size
    else:
        print("Erro: Variável já existe")
        parser.success = False

def p_Corpo(p):
    "Corpo    : Proc"
    p[0] = p[1]

def p_Corpo_Recursiva(p):
    "Corpo    : Proc Corpo"
    p[0] = f'{p[1]}{p[2]}'

def p_Proc_Atrib(p):
    "Proc     : Atrib"
    p[0] = p[1]

def p_Proc_Escrever(p):
    "Proc     : Escrever"
    p[0] = p[1]

def p_Proc_Se(p):
    "Proc     : Se"
    p[0] = p[1]

def p_Proc_Enquanto(p):
    "Proc     : Enquanto"
    p[0] = p[1]

def p_Se(p):
    "Se       : SE Cond ENTAO Corpo FIM"
    p[0] = f'{p[2]}JZ l{p.parser.labels}\n{p[4]}l{p.parser.labels}: nop\n'
    p.parser.labels += 1

def p_Se_Senao(p):
    "Se       : SE Cond ENTAO Corpo SENAO Corpo FIM"
    p[0] = f'{p[2]}JZ l{p.parser.labels}\n{p[4]}JUMP l{p.parser.labels}f\nl{p.parser.labels}: nop\n{p[6]}l{p.parser.labels}f: nop\n'
    p.parser.labels += 1

def p_Enquanto(p):
    "Enquanto : ENQUANTO Cond FAZ Corpo FIM"
    p[0] = f'l{p.parser.labels}c: NOP\n{p[2]}JZ l{p.parser.labels}f\n{p[4]}JUMP l{p.parser.labels}c\nl{p.parser.labels}f: NOP\n'
    p.parser.labels += 1

def p_Atrib_expr_Int(p):
    "Atrib    : NOME ATR Expr"
    if p[1] in p.parser.registers:
        if p[1] in p.parser.ints:
            p[0] = f'{p[3]}STOREG {p.parser.registers.get(p[1])}\n'
        else:
            print("Erro: Variável não é de tipo inteiro.")
            parser.success = False

    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Atrib_expr_Array(p):
    "Atrib    : NOME PRABRIR Expr PRFECHAR ATR Expr"
    if p[1] in p.parser.registers:
        p[0] = f'PUSHGP\nPUSHI {p.parser.registers.get(p[1])}\nPADD\n{p[3]}{p[6]}STOREN\n'
    else:
        print("Erro: Variável não definida.")

def p_Atrib_expr_Matriz(p):
    "Atrib    : NOME PRABRIR Expr VIRG Expr PRFECHAR ATR Expr"
    if p[1] in p.parser.registers:
        c = p.parser.registers.get(p[1])[2]
        p[0] = f'PUSHGP\nPUSHI {p.parser.registers.get(p[1])[0]}\nPADD\n{p[3]}PUSHI {c}\nMUL\n{p[5]}ADD\n{p[8]}STOREN\n'
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Atrib_Ler_Array(p):
    "Atrib    : NOME PRABRIR Expr PRFECHAR ATR LER"
    if p[1] in p.parser.registers:
        p[0] = f'PUSHGP\nPUSHI {p.parser.registers.get(p[1])}\nPADD\n{p[3]}READ\nATOI\nSTOREN\n'
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Atrib_Ler_Matriz(p):
    "Atrib    : NOME PRABRIR Expr VIRG Expr PRFECHAR ATR LER"
    if p[1] in p.parser.registers:
        c = p.parser.registers.get(p[1])[2]
        p[0] = f'PUSHGP\nPUSHI {p.parser.registers.get(p[1])[0]}\nPADD\n{p[3]}PUSHI {c}\nMUL\n{p[5]}ADD\nREAD\nATOI\nSTOREN\n'
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Atrib_Ler(p):
    "Atrib    : NOME ATR LER"
    if p[1] in p.parser.registers:
        p[0] = f'READ\nATOI\nSTOREG {p.parser.registers.get(p[1])}\n'
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Escrever(p):
    "Escrever : ESCREVER Expr"
    p[0] = f'{p[2]}WRITEI\nPUSHS "\\n"\nWRITES\n'

def p_Expr_Var(p):
    "Expr     : Var"
    p[0] = p[1]

def p_Expr_Num(p):
    "Expr     : Num"
    p[0] = p[1]

def p_Expr_Soma(p):
    "Expr     : SOMA PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}ADD\n'

def p_Expr_Sub(p):
    "Expr     : SUB PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}SUB\n'

def p_Expr_Mult(p):
    "Expr     : MULT PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}MUL\n'

def p_Expr_Div(p):
    "Expr     : DIV PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}DIV\n'

def p_Expr_Mod(p):
    "Expr     : MOD PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}MOD\n'

def p_Expr_Cond(p):
    "Expr     : Cond"
    p[0] = p[1]

def p_Cond_Maior(p):
    "Cond     : MAIOR PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}SUP\n'

def p_Cond_Menor(p):
    "Cond     : MENOR PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}INF\n'

def p_Cond_Maiori(p):
    "Cond     : MAIORI PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}SUPEQ\n'

def p_Cond_Menori(p):
    "Cond     : MENORI PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}INFEQ\n'

def p_Cond_Igual(p):
    "Cond     : IGUAL PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}EQUAL\n'

def p_Cond_Nigual(p):
    "Cond     : NIGUAL PCABRIR Expr VIRG Expr PCFECHAR"
    p[0] = f'{p[3]}{p[5]}EQUAL\nNOT\n'

def p_Cond_E(p):
    "Cond     : E PCABRIR Cond VIRG Cond PCFECHAR"
    p[0] = f'{p[3]}{p[5]}EQUAL\n'

def p_Cond_Ou(p):
    "Cond     : OU PCABRIR Cond VIRG Cond PCFECHAR"
    p[0] = f'{p[3]}{p[5]}ADD\nPUSHI 1\nSUPEQ\n'

def p_Cond_Neg(p):
    "Cond     : NEG PCABRIR Cond PCFECHAR"
    p[0] = f'{p[3]}NOT\n'

def p_Var_Matriz(p):
    "Var      : NOME PRABRIR Expr VIRG Expr PRFECHAR"
    if p[1] in p.parser.registers:
        c = p.parser.registers.get(p[1])[2]
        p[0] = f'PUSHGP\nPUSHI {p.parser.registers.get(p[1])[0]}\nPADD\n{p[3]}PUSHI {c}\nMUL\n{p[5]}ADD\nLOADN\n'
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Var_Array(p):
    "Var      : NOME PRABRIR Expr PRFECHAR"
    if p[1] in p.parser.registers:
        p[0] = f'PUSHGP\nPUSHI {p.parser.registers.get(p[1])}\nPADD\n{p[3]}LOADN\n'
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Var_Int(p):
    "Var      : NOME"
    if p[1] in p.parser.registers:
        if p[1] in p.parser.ints:
            p[0] = f'PUSHG {p.parser.registers.get(p[1])}\n'
        else:
            print("Erro: Variável não é de tipo inteiro.")
            parser.success = False
    else:
        print("Erro: Variável não definida.")
        parser.success = False

def p_Num(p):
    "Num      : NUM"
    p[0] = f'PUSHI {p[1]}\n'

#----------------------------------------
def p_error(p):
    print('Syntax error: ', p)
    parser.success = False

#----------------------------------------
#inicio do Parser e Calculadora
parser = yacc.yacc()

parser.success = True
parser.registers = {}
parser.labels = 0
parser.gp = 0
parser.ints = []

'''
for line in sys.stdin:
    parser.parse(line)
'''
with open(sys.argv[1],'r') as file:
    inp = file.read()
    parser.parse(inp)

