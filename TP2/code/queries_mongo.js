// RE01 - Listar os clientes que frequentaram o estabelecimento

// RE02 – Listar os edifícios e respetivos alojamentos

// RE03 - Listar todas as reservas realizadas num certo alojamento

// RE04 – Listar todos os funcionários e respetivo responsável
db.Funcionario.find({}, { Nome: 1, Gerente: 1 });
