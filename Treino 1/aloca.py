# aloca.py
def aloca(prefs):
    projetos = []
    result = []
    numeros = [x for x in prefs.keys()]
    numeros.sort()
    for aluno in numeros:
        preferencias = prefs[aluno]
        alocado = False
        for num in preferencias:
            if num not in projetos:
                projetos.append(num)
                alocado = True
                break
        if not alocado:
            result.append(aluno)
    return result
