CREATE DATABASE IF NOT EXISTS Uffici_postali;
USE Uffici_postali;

CREATE TABLE UFFICI (
    nome VARCHAR(30),
    citta VARCHAR(50),
    indirizzo VARCHAR(100),
    PRIMARY KEY (nome)
);

CREATE TABLE CLIENTI (
    codfisc VARCHAR(16),
    nome VARCHAR(50),
    cognome VARCHAR(50),
    indirizzo VARCHAR(100) NOT NULL,
    telefono VARCHAR(10),
    PRIMARY KEY (codfisc)
);

CREATE TABLE PACCHETTI (
    id INT,
    cf_mittente VARCHAR(16) NOT NULL,
    indirizzo_dest VARCHAR(100) NOT NULL,
    tracking_number INT NOT NULL,
    peso DECIMAL(10,2),
    Nufficio VARCHAR(30),
    FOREIGN KEY (cf_mittente) REFERENCES CLIENTI(codfisc),
    FOREIGN KEY (Nufficio) REFERENCES UFFICI(nome)
);

CREATE TABLE IMPIEGATI (
    cf VARCHAR(16),
    nome VARCHAR(50),
    cognome VARCHAR(50),
    data_inizio_lavoro DATE,
    salario INT,
    Nufficio VARCHAR(30),
    FOREIGN KEY (Nufficio) REFERENCES UFFICI(nome)
);
