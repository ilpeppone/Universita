CREATE SCHEMA IF NOT EXISTS Centro_medico ;

USE Centro_medico;

CREATE TABLE Medico(
    id INT NOT NULL PRIMARY KEY,
    nome CHAR (20),
    cognome CHAR(20),
    email CHAR(200)
);

CREATE TABLE Specializzazione (
    id INT PRIMARY KEY,
    nome CHAR (200)
);

CREATE TABLE Medico_specializzazione(
    id_medico INT, 
    id_specializzazione INT,
    FOREIGN KEY (id_medico) REFERENCES Medico(id),
    FOREIGN KEY (id_specializzazione) REFERENCES Specializzazione(id)
);

CREATE TABLE Paziente(
    id INT NOT NULL PRIMARY KEY,
    nome CHAR (20),
    cognome CHAR (20),
    data_di_nascita DATE
);

CREATE TABLE Visita(
    id INT NOT NULL,
    id_medico INT,
    id_paziente INT,
    data_visita DATE,
    FOREIGN KEY (id_medico) REFERENCES Medico(id),
    FOREIGN KEY (id_paziente) REFERENCES Paziente(id)
);