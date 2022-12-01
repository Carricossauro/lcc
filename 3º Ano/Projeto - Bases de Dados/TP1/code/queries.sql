USE AlojamentoLocal;

-- RE01 - Listar os clientes que frequentaram o estabelecimento;
SELECT Id_Cliente, Nome, `E-mail`, Telemovel FROM Cliente
	WHERE Id_Cliente IN 
	(SELECT Cliente FROM Reserva);

-- RE02 – Listar os edifícios e respetivos alojamentos
SELECT E.Id_Edificio, E.`Rua/Morada`, A.Numero AS Numero_Alojamento, A.Numero_Quartos, A.Lotacao FROM Edificio AS E
	INNER JOIN Alojamento AS A
		ON A.Edificio = E.Id_Edificio
    ORDER BY Id_Edificio;
    
-- RE03 - Listar todas as reservas realizadas num certo alojamento
SELECT RA.Reserva, R.Data_Inicio, R.Data_Fim FROM Reserva_Alojamento AS RA 
    INNER JOIN Reserva AS R
		ON R.Id_Reserva = RA.Reserva
	WHERE Alojamento = 1;

-- RE04 – Listar todos os funcionários e respetivo responsável
SELECT Id_Funcionario, Nome, Gerente FROM Funcionario;

-- RE05 – Calcular o número de vezes que cada alojamento foi reservado
SELECT P.Id_Alojamento, P.Numero, P.Edificio, COUNT(P.Reserva) AS Total_Reservas FROM
	(SELECT A.Id_Alojamento, A.Numero, A.Edificio, RA.Reserva FROM Reserva_Alojamento AS RA
		INNER JOIN Alojamento AS A
			ON A.Id_Alojamento = RA.Alojamento) AS P
	GROUP BY Id_Alojamento; 

-- RE06 – Calcular o número de pedidos que um funcionário processou
SELECT R.Funcionario, F.Nome, COUNT(R.Id_Reserva) AS Total_Reservas FROM Reserva AS R
	INNER JOIN Funcionario AS F
		ON F.Id_Funcionario = R.Funcionario
	GROUP BY Funcionario;
        
-- RE07 – Listar quantos quartos estão disponíveis até um certo preço
SELECT COUNT(Id_Alojamento) FROM Alojamento WHERE Preco_Base <= 100;

-- RE08 - Listar os clientes por ordem descrescente de dinheiro gasto
SELECT R.Cliente, C.Nome, SUM(R.Preco) AS Total_Gasto FROM Reserva AS R
	INNER JOIN Cliente AS C
		ON C.Id_Cliente = R.Cliente
    GROUP BY R.Cliente
    ORDER BY Total_Gasto DESC;