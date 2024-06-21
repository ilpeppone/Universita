CREATE SCHEMA IF NOT EXISTS Uffici_postali ;

USE Uffici_postali;

CREATE TABLE Clienti(
    codfisc CHAR(16) NOT NULL PRIMARY KEY,
    nome CHAR(20),
    cognome CHAR(20),
    indirizzo CHAR(200) NOT NULL,
    telefono CHAR(10)
);

CREATE TABLE Uffici(
    nome CHAR (20) PRIMARY KEY,
    citta CHAR (100),
    indirizzo CHAR (200)
);

CREATE TABLE Pacchetti(
    id INT ,
    cf_mittente CHAR(16) NOT NULL,
    indirizzo_dest CHAR(200) NOT NULL,
    tracking_number INT PRIMARY KEY NOT NULL,
    peso DECIMAL (10,2),
    Nufficio CHAR(20),
    FOREIGN KEY (cf_mittente) REFERENCES Clienti(codfisc),
    FOREIGN KEY (Nufficio) REFERENCES Uffici(nome)
);

CREATE TABLE Impiegati(
    cf CHAR(16),
    nome CHAR(20),
    cognome CHAR(20),
    data_inizio_lavoro DATE,
    salario int,
    Nufficio CHAR(20),
    FOREIGN KEY (Nufficio) REFERENCES Uffici(nome)
);