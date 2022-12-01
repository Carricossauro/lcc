import re
import json

def a(ficheiro_nome):
	ficheiro = open(ficheiro_nome, 'r')

	linha = ficheiro.readline()
	frequencia = {}

	while linha:
		x = re.search(r'[0-9]{4}(-[0-9]{2}){2}', linha)
		if x:
			ano = x.group()[:4]
			if ano not in frequencia:
				frequencia[ano] = 1
			else:
				frequencia[ano] += 1

		linha = ficheiro.readline()

	ficheiro.close()
	return frequencia

def b(ficheiro_nome):
	ficheiro = open(ficheiro_nome, 'r')

	linha = ficheiro.readline()
	frequencia = {}
	anos = {}

	while linha:
		linha_dividida = re.split('::', linha)

		if len(linha_dividida) >= 2:

			ano = linha_dividida[1][:4]
			if ano not in anos:
				anos[ano] = {}


			for campo in linha_dividida[2:5]:
				listaPalavras = re.findall(r'[a-zA-Z]+', campo)
				for palavra in listaPalavras:
					if palavra not in frequencia:
						frequencia[palavra] = 1
					else:
						frequencia[palavra] += 1

					if palavra not in anos[ano]:
						anos[ano][palavra] = 1
					else:
						anos[ano][palavra] += 1

		linha = ficheiro.readline()

	ficheiro.close()

	nomes_mais_frequentes = {}

	for ano in anos:
		nomes_mais_frequentes[ano] = max(anos[ano], key=lambda x: anos[ano][x])

	return frequencia, sorted([(x, nomes_mais_frequentes[x]) for x in nomes_mais_frequentes])

def c(ficheiro_nome):
	ficheiro = open(ficheiro_nome, 'r')

	linha = ficheiro.readline()
	frequencia = {}

	while linha:
		lista = re.split(r',', linha)

		for elemento in lista[1:]:
			x = re.match(r'[a-zA-Z]*(Irmao|Tio|Sobrinh[ao]|Pai|[nN]et[ao]|Meio|[Aa]vo)[a-zA-Z ]*\.', elemento)
			if x:
				relacao = x.group()[:-1]
				if relacao not in frequencia:
					frequencia[relacao] = 1
				else:
					frequencia[relacao] += 1

		linha = ficheiro.readline()

	ficheiro.close()
	return frequencia

def validateJSON(jsonData):
    try:
        json.load(jsonData)
    except ValueError as err:
        return False
    return True

def d(ficheiro_nome):
	ler = open(ficheiro_nome, 'r')
	escrever = open("output.json",'w')
	escrever.write("[\n")
	lista = []

	for y in range(20):
		linha = ler.readline()
		escrever.write("{")
		campos = re.split(r'::', linha)
		chaves = ['numero', 'data', 'nome', 'pai', 'mae', 'informacao adicional']
		
		for x in range(len(campos)-1):
			if campos[x] != "":
				escrever.write(f"\n\"{chaves[x]}\": \"{campos[x]}\",")

		escrever.seek(escrever.tell()-1,0)

		escrever.write("\n}")
		if y == 19:
			escrever.write("\n")
		else:
			escrever.write(",\n")

	escrever.write("]")

	ler.close()
	escrever.close()

	ficheiro = open("output.json", 'r')
	res = validateJSON(ficheiro)
	ficheiro.close()
	return res

inpt = -1
ficheiro = 'processos.txt'
while inpt != '0':
	inpt = input(f"Ficheiro: {ficheiro}\nEscolha o que pretende fazer: " +
		"\n0. Sair" +
		"\na. Calcular a frequência de processos por ano" + 
		"\nb. Calcular a frequência de nomes" + 
		"\nc. Calcular a frequência dos vários tipos de relação" + 
		"\nd. Imprimir os 20 primeiros registos num ficheiro em formato Json" +
		"\ne. Alterar ficheiro de input\n")

	if inpt == "a":
		res = a(ficheiro)

		ipt = input("Introduza um ano (Sair - 0): ")
		while ipt != '0':
			if ipt not in res:
				print(f'{ipt}: 0')
			else:
				print(f'{ipt}: {res[ipt]}')

			ipt = input("Introduza um ano (Sair - 0): ")

	elif inpt == 'b':
		frequencia, nomes_mais_frequentes = b(ficheiro)

		ipt = input("Escolha o que pretende fazer: " +
			"\n0. Sair" + 
			"\n1. Calcular a frequência de um nome" + 
			"\n2. Calcular o nome mais frequente de um ano\n")
		while ipt != '0':
			if ipt == '1':
				nome = input("Introduza um nome (Sair - 0): ")
				while nome != '0':
					if nome not in frequencia:
						print(f'{nome}: 0')
					else:
						print(f'{nome}: {frequencia[nome]}')
					
					nome = input("Introduza um nome (Sair - 0): ")
			elif ipt == '2':
				ano = input("Introduza um ano (Sair - 0): ")
				while ano != '0':
					listaX = [x for x,y in nomes_mais_frequentes if x == ano]
					listaY = [y for x,y in nomes_mais_frequentes if x == ano]
					if ano not in listaX:
						print(f'{ano}: 0')
					else:
						print(f'{ano}: {listaY[0]}')
					
					ano = input("Introduza um ano (Sair - 0): ")
			else:
				print("Opção inválida.")

			ipt = input("Escolha o que pretende fazer: " +
				"\n0. Sair" + 
				"\n1. Calcular a frequência de um nome" + 
				"\n2. Calcular o nome mais frequente de um ano\n")
	elif inpt == 'c':
		print(c(ficheiro))
	elif inpt == 'd':
		print(d(ficheiro))
	elif inpt == 'e':
		ficheiro = input("Escolha o novo ficheiro: ")
	elif inpt != '0':
		print("Opção inválida.")