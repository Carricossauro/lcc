USE AlojamentoLocal;

-- RE01 - Listar os clientes que frequentaram o estabelecimento;
CREATE VIEW RE01 (Id, Nome) AS 
	SELECT Id_Cliente,Nome FROM Cliente
		WHERE Id_Cliente IN 
        (SELECT Cliente FROM Reserva);

-- RE02 – Listar os edifícios e respetivos quartos
CREATE VIEW RE02 (Id_Edificio, Morada, Numero_Quarto) AS
	SELECT E.Id_Edificio, E.`Rua/Morada`, A.Numero FROM Edificio AS E, Alojamento AS A
    ORDER BY Id_Edificio;
    
-- RE03 - IMPOSSIVEL
    
-- RE04 – Listar todos os funcionários e respetivo responsável
CREATE VIEW RE04 (Id_Funcionario, Nome, Responsavel) AS
	SELECT Id_Funcionario, Nome, Gerente FROM Funcionario;

-- RE05 – Calcular o número de vezes que cada quarto foi reservado
CREATE VIEW RE05 (Id_Alojamento, Numero_Alojamento, Edificio, Reservas) AS
	SELECT P.Id_Alojamento, P.Numero, P.Edificio, COUNT(P.Reserva) FROM
		(SELECT A.Id_Alojamento, A.Numero, A.Edificio, RA.Reserva FROM Reserva_Alojamento AS RA
			INNER JOIN Alojamento AS A
				ON A.Id_Alojamento = RA.Alojamento) AS P
		GROUP BY Id_Alojamento; 

-- RE06 – Calcular o número de pedidos que um funcionário processou
CREATE VIEW RE06 (Funcionario, Nome, Pedidos) AS
	SELECT R.Funcionario, F.Nome, COUNT(R.Id_Reserva) FROM Reserva AS R
		INNER JOIN Funcionario AS F
			ON F.Id_Funcionario = R.Funcionario
		GROUP BY Funcionario;
        
-- RE07 – IMPOSSIVEL