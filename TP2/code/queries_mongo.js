// RE01 - Listar os clientes que frequentaram o estabelecimento

db.Cliente.aggregate([
    {
        $lookup: {
            from: "Reserva",
            localField: "_id",
            foreignField: "Cliente",
            as: "Reservas",
        },
    },
]);

// RE02 – Listar os edifícios e respetivos alojamentos

db.Edificio.aggregate([
    {
        $lookup: {
            from: "Alojamento",
            localField: "_id",
            foreignField: "Edificio",
            as: "Alojamentos",
        },
    },
    {
        $project: {
            "Rua/Morada": 1,
            "Alojamentos.Numero": 1,
            "Alojamentos.Numero_Quartos": 1,
            "Alojamentos.Lotacao": 1,
        },
    },
]).sort({ _id: 1 });

// RE03 - Listar todas as reservas realizadas num certo alojamento

db.Alojamento.aggregate([
    { $match: {} },
    { $unwind: "$Reservas" },
    {
        $lookup: {
            from: "Reserva",
            localField: "Reservas.Reserva",
            foreignField: "_id",
            as: "Reserva",
        },
    },
    { $unwind: "$Reserva" },
    {
        $group: {
            _id: "$_id",
            Reservas: {
                $push: {
                    _id: "$Reserva._id",
                    Data_Inicio: "$Reserva.Data_Inicio",
                    Data_Fim: "$Reserva.Data_Fim",
                },
            },
        },
    },
]);

// RE04 – Listar todos os funcionários e respetivo responsável

db.Funcionario.find({}, { Nome: 1, Gerente: 1 });

// RE05 – Calcular o número de vezes que cada alojamento foi reservado

db.Alojamento.aggregate([
    { $match: {} },
    { $unwind: "$Reservas" },
    {
        $lookup: {
            from: "Reserva",
            localField: "Reservas.Reserva",
            foreignField: "_id",
            as: "Reserva",
        },
    },
    { $unwind: "$Reserva" },
    {
        $group: {
            _id: "$_id",
            Reservas: { $sum: 1 },
        },
    },
]);

// RE06 – Calcular o número de pedidos que um funcionário processou

db.Funcionario.aggregate([
    {
        $lookup: {
            from: "Reserva",
            localField: "_id",
            foreignField: "Funcionario",
            as: "Reservas",
        },
    },
    { $unwind: "$Reservas" },
    {
        $group: {
            _id: "$_id",
            Nome: { $first: "$Nome" },
            Reservas: { $sum: 1 },
        },
    },
]).sort({ _id: 1 });

// RE07 – Listar quantos quartos estão disponíveis até um certo preço

db.Alojamento.find({ Preco_Base: { $lte: 100 } });

// RE08 - Listar os clientes por ordem descrescente de dinheiro gasto

db.Reserva.aggregate([
    {
        $lookup: {
            from: "Cliente",
            localField: "Cliente",
            foreignField: "_id",
            as: "ClienteCol",
        },
    },
    { $unwind: "$ClienteCol" },
    { $unwind: "$Alojamentos" },
    {
        $group: {
            _id: "$Cliente",
            Nome: { $first: "$ClienteCol.Nome" },
            Total_Gasto: { $sum: "$Alojamentos.Preco" },
        },
    },
]).sort({ Total_Gasto: -1, _id: 1 });
