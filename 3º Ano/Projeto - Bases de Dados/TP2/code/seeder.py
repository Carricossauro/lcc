# SEEDERS
def gen_Cliente():
    Cliente = {
        "Nome": fake.name(),
        "Data_Nascimento": fake.date_between(
            datetime.date(1960, 1, 1),
            datetime.date(2001, 1, 1)
        ).strftime("%Y-%m-%d"),
        "E-mail": fake.free_email(),
        "Telemovel": fake.phone_number().replace(" ", "")[-9:]
    }

    return Cliente

def gen_Funcionario(gerente_id, nome="falso", salario=665):
    Funcionario = {
        "Nome": nome if nome != "falso" else fake.name(),
        "Telemovel": fake.phone_number().replace(" ", "")[-9:],
        "E-mail": fake.free_email(),
        "Salario": salario,
        "Gerente": gerente_id
    }

    return Funcionario

def gen_Edificio():
    Edificio = {
        "Rua/Morada": fake.street_address(),
        "Localidade/Morada": fake.concelho(),
        "Codigo_Postal/Morada": fake.postcode()
    }

    return Edificio

def gen_Alojamento(edificio_id, num, preco, lotacao, num_quartos):
    Alojamento = {
        "Edificio": edificio_id,
        "Numero": num,
        "Preco_Base": preco,
        "Lotacao": lotacao,
        "Numero_Quartos": num_quartos
    }

    return Alojamento

def gen_Reserva(num_funcionarios, cliente_id, start):
    data_ini = fake.date_between(
        start,
        start + datetime.timedelta(days=7)
    )

    data_fim = data_ini + datetime.timedelta(days=3)

    Reserva = {
        "Funcionario": random.randint(1, num_funcionarios),
        "Cliente": cliente_id,
        "Data_Inicio": data_ini.strftime("%Y-%m-%d"),
        "Data_Fim": data_fim.strftime("%Y-%m-%d"),
        "Adultos": random.randint(1, 3),
        "Criancas": random.randint(0, 3)
    }

    return Reserva

def gen_Reserva_Alojamento(reserva_id, alojamento_id, preco_base):
    Reserva_Alojamento = {
        "Reserva": reserva_id,
        "Alojamento": alojamento_id,
        "Preco": preco_base#round(preco_base*(1+random.randint(25, 60)/100), 2)
    }

    return Reserva_Alojamento

def dict2sql(table, dic):
    fields = str(tuple(dict[0].keys())).replace("'", "`")
    sql = f'INSERT INTO {table} {fields} VALUES '

    for entry in dic:
        sql += f'\n{tuple(entry.values())},'
    sql = sql[:-1] + ";\n\n"

    return sql


# IMPORTS
import datetime
import random
from faker import Faker


# CONSTANTS
fake = Faker(['pt_PT'])

E1 = [(3, 6, 190), (2, 4, 130), (2, 4, 130)]
E2 = [(1, 2, 70), (1, 2, 70), (2, 4, 130), (2, 4, 130)]

proprietario = {
    "Nome": "Luís Presa",
    "Telemovel": fake.phone_number().replace(" ", "")[-9:],
    "E-mail": "lpresa@sapo.com",
    "Salario": 1515,
    "Gerente": 'NULL'
}


# GENERATING DATA
Clientes = [gen_Cliente() for _ in range(100)]

Funcionarios = [gen_Funcionario(1) for _ in range(3)]
Funcionarios.insert(0, proprietario)

Edificios = [gen_Edificio() for _ in range(2)]

Alojamentos = [gen_Alojamento(1, n+1, E1[n][2], E1[n][1], E1[n][0]) for n in range(len(E1))]
Alojamentos += [gen_Alojamento(2, n+1, E2[n][2], E2[n][1], E2[n][0]) for n in range(len(E2))]

Reservas = []
data = datetime.date(2020, 1, 1)
for id in range(len(Clientes)):
    for _ in range(random.randint(1, 3)):
        Reservas.append(gen_Reserva(len(Funcionarios), (id+1), data))
        data += datetime.timedelta(days=4)

Reserva_Alojamentos = []
for id in range(len(Reservas)):
    ocupacao = Reservas[id]["Adultos"] + Reservas[id]["Criancas"]
    disp = [id_a+1 for id_a in range(len(Alojamentos)) if Alojamentos[id_a]["Lotacao"] >= ocupacao]
    sel = random.sample(disp, 1)[0]
    entry = gen_Reserva_Alojamento(
        (id+1),
        sel,
        Alojamentos[sel-1]["Preco_Base"]
    )
    Reserva_Alojamentos.append(entry)


# WRITING THE FILE
tabelas = [
    ("Cliente", Clientes), ("Funcionario", Funcionarios),
    ("Edificio", Edificios), ("Alojamento", Alojamentos),
    ("Reserva", Reservas), ("Reserva_Alojamento", Reserva_Alojamentos)
]

with open("povoamento.sql", "w") as file:
    for table, dict in tabelas:
        sql = dict2sql(table, dict)
        file.write(sql)

    file.close()


print(sql)
