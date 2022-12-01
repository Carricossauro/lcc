use AlojamentoLocal;

-- Calcular o valor total dos alugueres de cada quarto
select Alojamento, sum(Preco) from Reserva_Alojamento
	group by Alojamento;

-- RE07 – Listar os quartos que estão disponíveis até um certo preço
SELECT Id_Alojamento, Preco_Base FROM Alojamento WHERE Preco_Base <= 100;

-- RE08 - Listar os clientes por ordem descrescente de dinheiro gasto (Alterado para a nova estrutura)
SELECT R.Cliente, C.Nome, SUM(RA.Preco) AS Total_Gasto FROM Reserva AS R
	INNER JOIN Cliente AS C
		ON C.Id_Cliente = R.Cliente
	INNER JOIN Reserva_Alojamento AS RA
		ON RA.Reserva = R.Id_Reserva
    GROUP BY R.Cliente
    ORDER BY Total_Gasto DESC;