USE AlojamentoLocal;

-- V01 - Calcular o número de vezes que cada alojamento foi reservado
CREATE VIEW V01 AS
	SELECT P.Id_Alojamento, P.Numero, P.Edificio, COUNT(P.Reserva) AS Total_Reservas FROM
		(SELECT A.Id_Alojamento, A.Numero, A.Edificio, RA.Reserva FROM Reserva_Alojamento AS RA
			INNER JOIN Alojamento AS A
				ON A.Id_Alojamento = RA.Alojamento) AS P
		GROUP BY Id_Alojamento;