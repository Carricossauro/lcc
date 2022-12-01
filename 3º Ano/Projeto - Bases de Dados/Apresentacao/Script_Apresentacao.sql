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

-- RE07 – Listar os quartos que estão disponíveis até um certo preço
SELECT Id_Alojamento, Preco_Base FROM Alojamento WHERE Preco_Base <= 100;


-- RE08 - Listar os clientes por ordem descrescente de dinheiro gasto
SELECT R.Cliente, C.Nome, SUM(RA.Preco) AS Total_Gasto FROM Reserva AS R
    INNER JOIN Cliente AS C
        ON C.Id_Cliente = R.Cliente
    INNER JOIN Reserva_Alojamento AS RA
        ON RA.Reserva = R.Id_Reserva
    GROUP BY R.Cliente
    ORDER BY Total_Gasto DESC;
    
-- RE09 -  Calcular o valor total dos alugueres de cada quarto
select Alojamento, sum(Preco) from Reserva_Alojamento
    group by Alojamento;
    
-- V01 - Calcular o número de vezes que cada alojamento foi reservado
CREATE VIEW V01 AS
    SELECT P.Id_Alojamento, P.Numero, P.Edificio, COUNT(P.Reserva) AS Total_Reservas FROM
        (SELECT A.Id_Alojamento, A.Numero, A.Edificio, RA.Reserva FROM Reserva_Alojamento AS RA
            INNER JOIN Alojamento AS A
                ON A.Id_Alojamento = RA.Alojamento) AS P
        GROUP BY Id_Alojamento;
    
    
-- Atualiza o preço de um alojamento

DELIMITER $$
CREATE PROCEDURE UpdatePrecoAlojamento (in Percentagem int, in Id int) 
BEGIN
UPDATE Alojamento
  SET Preco_Base = Preco_Base * (1+Percentagem/100)
  WHERE Id_Alojamento = Id;
END $$

CALL UpdatePrecoAlojamento(3, 1);

Select * from Alojamento
where Id_Alojamento = 1;

-- Atualiza salário de um funcionário
DELIMITER $$
CREATE PROCEDURE UpdateSalarioFuncionario (in novoSalario int, in Id int) 
BEGIN
UPDATE Funcionario
  SET Salario = novoSalario
  WHERE Id_Funcionario = Id;
END $$

CALL UpdateSalarioFuncionario(955, 1);

Select * from Funcionario
where Id_Funcionario= 1;

-- Inserir uma reserva
INSERT into Reserva (Funcionario, Cliente, Data_Inicio, Data_Fim, Adultos, Criancas)
    values (1, 5,"2022-01-22 00:00:00","2022-01-24 23:59:59", 2, 4);

INSERT INTO Reserva_Alojamento (Reserva, Alojamento, Preco)
    values((Select LAST_INSERT_ID()), 1, (Select Preco_Base from Alojamento where Id_Alojamento = 1));

Select * from Reserva;
Select * from Reserva_Alojamento;

-- Apagar uma reserva

DELETE from Reserva_Alojamento where Reserva = 219;
DELETE from Reserva where Id_Reserva = 219;

Select * from Reserva;
Select * from Reserva_Alojamento;
