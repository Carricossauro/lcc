
# 100%
def search(ops, res, k, n, i):
    if k == i:
        return res == n
        
    for what in ops:
        cI = n
        if '+' in what:
            what = what.split('+')
            cI += int(what[1])
        elif '-' in what:
            what = what.split('-')
            cI -= int(what[1])
        elif '/' in what:
            what = what.split('/')
            cI //= int(what[1])
        elif '*' in what:
            what = what.split('*')
            cI *= int(what[1])
        else:
            cI = int(str(cI) + str(what))
        if search(ops, res, k, cI, i+1):
            return True

    return False

def calculadora(ops,res):
    print(ops, res)
    k = 0
    while True:
        if search(ops,res,k, 0, 0):
            return k
        k+=1
    return -1
