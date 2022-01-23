// RE01 - Listar os clientes que frequentaram o estabelecimento

db.Cliente.aggregate( [
   {
     $lookup: {
         from: "Reserva",
         localField: "_id",
         foreignField: "Cliente",
         as: "Reservas"
     }
   }
] )

// RE02 – Listar os edifícios e respetivos alojamentos

db.Edificio.aggregate( [
   {
     $lookup: {
         from: "Alojamento",
         localField: "_id",
         foreignField: "Edificio",
         as: "Alojamentos"
     }
   }
] )

// RE03 - Listar todas as reservas realizadas num certo alojamento

// RE04 – Listar todos os funcionários e respetivo responsável

db.Funcionario.find({}, { Nome: 1, Gerente: 1 });

// RE05 – Calcular o número de vezes que cada alojamento foi reservado

// RE06 – Calcular o número de pedidos que um funcionário processou

db.Reserva.aggregate([{ $count: "Funcionario" }])
db.Reserva.aggregate([{$group: {_id: "Funcionario", count: {$sum: 1} } }])

// RE07 – Listar quantos quartos estão disponíveis até um certo preço

db.Alojamento.find( { Preco_Base: { $lte: 100 } } )

// RE08 - Listar os clientes por ordem descrescente de dinheiro gasto

db.Reserva.aggregate([ {$unwind: "$Alojamentos"}, { $group: { _id: "$Cliente", Nome: {$sum: "Cliente_Dados.Nome"}, Total_Gasto: { $sum: "$Alojamentos.Preco" } } }]).sort({Total_Gasto: -1, "_id": 1})
