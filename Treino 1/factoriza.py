'''
Defina uma função que recebe um número positivo
e produz a soma dos seus factores primos distintos.
'''

def isPrime(x):
    r = True
    for k in range(2,x//2+1):
        if x % k == 0:
            r = False
            break
    return r
    
def factoriza(n):
    primos = [x for x in range(2,n+1) if isPrime(x)]
    result = 0
    for k in primos:
        if (n % k == 0):
            result += k

    return result

# It's Big Brain Time

def factoriza(n):
    primos = [x for x in range(2,n+1) if all([x % k != 0 for k in range(2,x//2+1)])]
    result = 0
    for k in primos:
        if (n % k == 0):
            result += k

    return result

# Even Bigger Brain Time

def factoriza(n):
    primos = [x for x in range(2,n+1) if all([x % k != 0 for k in range(2,x//2+1)])]
    result = sum(filter(lambda x: n % x == 0, primos))
    return result
