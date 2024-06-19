USE Lavoratori;

CREATE TABLE Dipartimento(
    CodD INT NOT NULL PRIMARY KEY,
    NomeD CHAR(50),
    Indirizzo CHAR(200),
    Citta CHAR(100)
);

CREATE TABLE Impiegato(
    CodFisc CHAR(18) NOT NULL PRIMARY KEY,
    Nome CHAR(20),
    Cognome CHAR(20),
    Recapito CHAR(20),
    Dip INT,
    FOREIGN KEY (Dip) REFERENCES Dipartimento (CodD)
);

CREATE TABLE Progetto(
    CodP INT NOT NULL PRIMARY KEY,
    NomeP CHAR(200),
    Budget DECIMAL(10,2)
);

CREATE TABLE Lavora_Su(
    Imp CHAR(18),
    FOREIGN KEY (Imp) REFERENCES Impiegato (CodFisc),
    Prog INT,
    FOREIGN KEY (Prog) REFERENCES Progetto(CodP)
);