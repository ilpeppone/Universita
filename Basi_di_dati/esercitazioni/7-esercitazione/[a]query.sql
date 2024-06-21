CREATE SCHEMA IF NOT EXISTS Televisione;

USE Televisione;

CREATE TABLE Programmi(
    Codice CHAR(16) NOT NULL PRIMARY KEY,
    NomeProgramma CHAR(200),
    Rete INT,
    Tipologia CHAR(200)
);

CREATE TABLE Artisti(
    CProgramma CHAR(16),
    FOREIGN KEY (CProgramma) REFERENCES Programmi(Codice),
    NomeArt CHAR(100) NOT NULL PRIMARY KEY
);

CREATE TABLE Sondaggi(
    CodProg CHAR(16),
    FOREIGN KEY (CodProg) REFERENCES Programmi (Codice),
    Auditel INT
);

