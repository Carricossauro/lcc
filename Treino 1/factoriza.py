'''
Defina uma função que recebe um número positivo
e produz a soma dos seus factores primos distintos.
'''

def isPrime(x):
    r = True
    for k in range(2,x//2):
        if x % k == 0:
            r = False
            break
    return r
    
def factoriza(n):
    primos = [x for x in range(2,100) if isPrime(x)]
    result = 0
    for k in primos:
        if (n % k == 0):
            result += k
        while (n % k == 0):
            n//=k

    return result
