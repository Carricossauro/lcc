#!/usr/bin/python3

import decimal
import datetime
import mysql.connector
import pymongo

mongoClient = pymongo.MongoClient("mongodb://localhost:27017/")
mongoDb = mongoClient["AlojamentoLocal"]

db = mysql.connector.connect(
    host = "localhost",
    user = "universidade",
    password  = "universidade",
    database = "AlojamentoLocal"
)

def migracao(tabela, atributos):
    cursor = db.cursor()
    cursor.execute(f"select * from {tabela}")
    res = []
    for row in cursor:
        obj = []
        for i in range(len(row)):
            if isinstance(row[i], decimal.Decimal):
                obj.append(float(row[i]))
            elif isinstance(row[i], datetime.date):
                obj.append(datetime.datetime(row[i].year, row[i].month, row[i].day))
            else:
                obj.append(row[i])
        res.append(tuple(obj))

    lista = []
    for el in res:
        lista.append({})
        for i in range(len(el)):
            lista[-1][atributos[i]] = el[i]

    mongoColection = mongoDb[tabela]
    mongoColection.drop()
    x = mongoColection.insert_many(lista)

    return x.inserted_ids

##################################
# Edificio
##################################

atributos = ["_id", "Rua/Morada", "Localidade/Morada", "Codigo_Postal/Localidade"]

print(migracao("Edificio", atributos))

##################################
# Alojamento
##################################

atributos = ["_id", "Numero", "Edificio", "Preco_Base", "Lotacao", "Numero_Quartos"]

print(migracao("Alojamento", atributos))

##################################
# Funcionario
##################################

atributos = ["_id", "Nome", "Telemovel", "E-mail", "Salario", "Gerente"]

print(migracao("Funcionario", atributos))

##################################
# Cliente
##################################

atributos = ["_id", "Nome", "Data_Nascimento", "E-mail", "Telemovel"]

print(migracao("Cliente", atributos))

##################################
# Reserva
##################################

atributos = ["_id", "Funcionario", "Cliente", "Data_Inicio", "Data_Fim", "Preco", "Adultos", "Criancas"]

print(migracao("Reserva", atributos))

##################################
# Reserva_Alojamento
##################################

atributos = ["_id", "Reserva", "Alojamento"]

print(migracao("Reserva_Alojamento", atributos))