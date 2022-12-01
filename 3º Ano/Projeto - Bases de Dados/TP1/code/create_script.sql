-- -----------------------------------------------------
-- Schema AlojamentoLocal
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS AlojamentoLocal DEFAULT CHARACTER SET utf8 ;
USE AlojamentoLocal ;

-- -----------------------------------------------------
-- Table AlojamentoLocal.Edificio
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS AlojamentoLocal.Edificio (
  Id_Edificio INT NOT NULL AUTO_INCREMENT,
  `Rua/Morada` VARCHAR(200) NOT NULL,
  `Localidade/Morada` VARCHAR(100) NOT NULL,
  `Codigo_Postal/Morada` VARCHAR(10) NOT NULL,
  PRIMARY KEY (Id_Edificio))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table AlojamentoLocal.Alojamento
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS AlojamentoLocal.Alojamento (
  Id_Alojamento INT NOT NULL AUTO_INCREMENT,
  Numero INT NOT NULL,
  Edificio INT NOT NULL,
  Preco_Base DECIMAL(6,2) NOT NULL,
  Lotacao INT NOT NULL,
  Numero_Quartos INT NOT NULL,
  INDEX fk_Quartos_Edificio1_idx (Edificio ASC),
  PRIMARY KEY (Id_Alojamento),
  CONSTRAINT fk_Quartos_Edificio1
    FOREIGN KEY (Edificio)
    REFERENCES AlojamentoLocal.Edificio (Id_Edificio)
  )
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table AlojamentoLocal.Funcionario
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS AlojamentoLocal.Funcionario (
  Id_Funcionario INT NOT NULL AUTO_INCREMENT,
  Nome VARCHAR(200) NOT NULL,
  Telemovel INT NOT NULL,
  `E-mail` VARCHAR(200) NOT NULL,
  Salario INT NOT NULL,
  Gerente INT,
  PRIMARY KEY (Id_Funcionario),
  INDEX funcionario_gerente_idx (Gerente ASC),
  CONSTRAINT funcionario_gerente
    FOREIGN KEY (Gerente)
    REFERENCES AlojamentoLocal.Funcionario (Id_Funcionario)
  )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table AlojamentoLocal.Cliente
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS AlojamentoLocal.Cliente (
  Id_Cliente INT NOT NULL AUTO_INCREMENT,
  Nome VARCHAR(200) NOT NULL,
  Data_Nascimento DATE NOT NULL,
  `E-mail` VARCHAR(200) NOT NULL,
  Telemovel INT NOT NULL,
  PRIMARY KEY (Id_Cliente))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table AlojamentoLocal.Reserva
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS AlojamentoLocal.Reserva (
  Id_Reserva INT NOT NULL AUTO_INCREMENT,
  Funcionario INT NOT NULL,
  Cliente INT NOT NULL,
  Data_Inicio DATETIME NOT NULL,
  Data_Fim DATETIME NOT NULL,
  Preco DECIMAL(6,2) NOT NULL,
  Adultos INT NOT NULL,
  Criancas INT NOT NULL,
  PRIMARY KEY (Id_Reserva),
  INDEX fk_Reservas_Funcionarios1_idx (Funcionario ASC),
  INDEX fk_Reserva_Cliente1_idx (Cliente ASC),
  CONSTRAINT fk_Reservas_Funcionarios1
    FOREIGN KEY (Funcionario)
    REFERENCES AlojamentoLocal.Funcionario (Id_Funcionario),
  CONSTRAINT fk_Reserva_Cliente1
    FOREIGN KEY (Cliente)
    REFERENCES AlojamentoLocal.Cliente (Id_Cliente)
  )
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table AlojamentoLocal.Reserva_Alojamento
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS AlojamentoLocal.Reserva_Alojamento (
  Reserva INT NOT NULL,
  Alojamento INT NOT NULL,
  PRIMARY KEY (Reserva, Alojamento),
  INDEX fk_Reserva_Quarto_Quarto1_idx (Alojamento ASC),
  CONSTRAINT fk_Reserva_Quarto_Reserva1
    FOREIGN KEY (Reserva)
    REFERENCES AlojamentoLocal.Reserva (Id_Reserva),
  CONSTRAINT fk_Reserva_Quarto_Quarto1
    FOREIGN KEY (Alojamento)
    REFERENCES AlojamentoLocal.Alojamento (Id_Alojamento)
  )
ENGINE = InnoDB;