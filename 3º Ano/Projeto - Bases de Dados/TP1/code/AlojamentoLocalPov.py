# https://towardsdatascience.com/generating-random-data-into-a-database-using-python-fd2f7d54024e

import pandas as pd
import random
from faker import Faker
from collections import defaultdict 
from sqlalchemy import create_engine

fake = Faker(['pt_PT'])

n_rows = 100


Cliente = defaultdict(list)
for _ in range(n_rows):
    Cliente["Nome"].append(fake.name())
    Cliente["Data_Nascimento"].append(fake.date_of_birth())
    Cliente["E-mail"].append(fake.free_email())
    Cliente["Telemovel"].append(fake.phone_number())


Edificio = defaultdict(list)
for _ in range(n_rows):
    Edificio["Rua/Morada"].append(fake.street_address())
    Edificio["Localidade/Morada"].append(fake.concelho())
    Edificio["Codigo_Postal/Morada"].append(fake.postcode())


Funcionario = defaultdict(list)
for i in range(n_rows):
    Funcionario["Nome"].append(fake.name())
    Funcionario["Telemovel"].append(fake.phone_number())
    Funcionario["E-mail"].append(fake.free_email())
    Funcionario["Salario"].append(random.randint(765, 1237))
    # TODO ver melhor esta chave estrangeira
    Funcionario["Gerente"].append(random.randint(1, i))


Funcionario_Edificio = defaultdict(list)
for _ in range(n_rows):
	# TODO mudar isto para ir buscar consoante o número de funcionarios e de edificios
	Funcionario_Edificio["Funcionario"].append(random.randint(1, i))
    Funcionario_Edificio["Edificio"].append(random.randint(1, i))


Reserva = defaultdict(list)
for _ in range(n_rows):
	# TODO mudar isto para ir buscar consoante o número de funcionarios e de clientes
    Reserva["Funcionario"].append(random.randint(1, n))
    Reserva["Cliente"].append(random.randint(1, n))
    Reserva["Data_Inicio"].append(fake.date_between(datetime.date(2020, 8, 22), datetime.date(2021, 1, 6)))
    Reserva["Data_Fim"].append(fake.date_between(datetime.date(2020, 8, 22), datetime.date(2021, 1, 6)))
    Reserva["Preco"].append(random.randint(200, 350))
    Reserva["Adultos"].append(random.randint(1, 2))
    Reserva["Criancas"].append(random.randint(0, 3))


Reserva_Alojamento = defaultdict(list)
for _ in range(n_rows):
	# TODO mudar isto para ir buscar consoante o número de Reservas e de Alojamento
    Reserva_Alojamento["Reserva"].append(random.randint(1, n))
    Reserva_Alojamento["Alojamento"].append(random.randint(1, n))


Alojamento = defaultdict(list)
for _ in range(n_rows):
	# TODO mudar isto para ir buscar consoante o número de Edificios
    Alojamento["Edificio"].append(random.randint(1, n))
    Alojamento["Numero"].append(random.randint(1, n)) ## TODO não sei isto como tem de ficar
    Alojamento["Preco_Base"].append(random.randint(80, 150))
    Alojamento["Lotacao"].append(random.randint(1, n))




df_cliente = pd.DataFrame(cliente)

engine = create_engine('mysql://root:@localhost/testdb', echo=False)


df_cliente.to_sql('user', con=engine,index=False)


