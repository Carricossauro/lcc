-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema ComputationalMind
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema ComputationalMind
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `ComputationalMind` ;
USE `ComputationalMind` ;

-- -----------------------------------------------------
-- Table `ComputationalMind`.`Player`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ComputationalMind`.`Player` (
  `Id` VARCHAR(75) NOT NULL,
  `Name` VARCHAR(75) NOT NULL,
  `Password` VARCHAR(256) NOT NULL,
  `Birthday` DATE NULL,
  `Email` VARCHAR(75) NOT NULL,
  PRIMARY KEY (`Id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ComputationalMind`.`Author`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ComputationalMind`.`Author` (
  `Id` VARCHAR(75) NOT NULL,
  `Name` VARCHAR(75) NOT NULL,
  `Password` VARCHAR(256) NOT NULL,
  `Email` VARCHAR(75) NOT NULL,
  PRIMARY KEY (`Id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ComputationalMind`.`Question`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ComputationalMind`.`Question` (
  `Id` INT NOT NULL AUTO_INCREMENT,
  `Author` VARCHAR(75) NOT NULL,
  `Title` VARCHAR(45) NOT NULL,
  `Type` ENUM("SA", "TF", "MC") NOT NULL,
  `Score` INT NOT NULL,
  `Dificulty` ENUM("Easy", "Medium", "Hard") NOT NULL,
  `MinAge` INT NOT NULL,
  `MaxAge` INT NOT NULL,
  PRIMARY KEY (`Id`),
  INDEX `fk_Question_1_idx` (`Author` ASC) VISIBLE,
  CONSTRAINT `fk_Question_1`
    FOREIGN KEY (`Author`)
    REFERENCES `ComputationalMind`.`Author` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ComputationalMind`.`Option`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ComputationalMind`.`Option` (
  `Id` INT NOT NULL AUTO_INCREMENT,
  `Question` INT NOT NULL,
  `Answer` TEXT NOT NULL,
  `Correct` TINYINT NOT NULL,
  PRIMARY KEY (`Id`),
  INDEX `fk_Option_1_idx` (`Question` ASC) VISIBLE,
  CONSTRAINT `fk_Option_1`
    FOREIGN KEY (`Question`)
    REFERENCES `ComputationalMind`.`Question` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ComputationalMind`.`Content`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ComputationalMind`.`Content` (
  `Id` INT NOT NULL AUTO_INCREMENT,
  `Question` INT NOT NULL,
  `Order` INT NOT NULL,
  `Type` ENUM("V", "I", "A", "T") NOT NULL,
  PRIMARY KEY (`Id`),
  CONSTRAINT `fk_Content_1`
    FOREIGN KEY (`Question`)
    REFERENCES `ComputationalMind`.`Question` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ComputationalMind`.`History`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ComputationalMind`.`History` (
  `Id` INT NOT NULL AUTO_INCREMENT,
  `Player` VARCHAR(75) NOT NULL,
  `Question` INT NOT NULL,
  `Date` DATETIME NOT NULL,
  `Correct` TINYINT NOT NULL,
  `Answer` TEXT NOT NULL,
  PRIMARY KEY (`Id`),
  INDEX `fk_History_1_idx` (`Player` ASC) VISIBLE,
  INDEX `fk_History_2_idx` (`Question` ASC) VISIBLE,
  CONSTRAINT `fk_History_1`
    FOREIGN KEY (`Player`)
    REFERENCES `ComputationalMind`.`Player` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_History_2`
    FOREIGN KEY (`Question`)
    REFERENCES `ComputationalMind`.`Question` (`Id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
