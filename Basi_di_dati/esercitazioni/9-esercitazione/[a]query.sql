CREATE SCHEMA IF NOT EXISTS Ecommerce ;


USE Ecommerce;

CREATE TABLE Utente(
    username CHAR(100) NOT NULL PRIMARY KEY,
    nome CHAR(50),
    cognome CHAR(50),
    email CHAR(200)
);

CREATE TABLE Prodotto(
    nome CHAR(200) NOT NULL PRIMARY KEY,
    prezzo DECIMAL (10,2),
    quantita INT
);

CREATE TABLE Ordine(
    codice INT NOT NULL PRIMARY KEY,
    data_ordine DATE,
    stato CHAR (100),
    username_utente CHAR (100),
    FOREIGN KEY (username_utente) REFERENCES Utente(username)
);

CREATE TABLE Categoria_prod(
    nome CHAR(200),
    categoria CHAR(50),
    FOREIGN KEY (nome) REFERENCES Prodotto(nome)
);

CREATE TABLE Composto(
    nome CHAR(200),
    codice INT,
    quantita INT,
    FOREIGN KEY (nome) REFERENCES Prodotto(nome),
    FOREIGN KEY (codice) REFERENCES Ordine(codice)
);

CREATE TABLE Spedizione(
    codice INT,
    FOREIGN KEY (codice) REFERENCES Ordine(codice),
    data_di_sped DATE,
    indirizzo CHAR (200)
);