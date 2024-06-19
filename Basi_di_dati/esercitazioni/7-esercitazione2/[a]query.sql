USE Elezioni;

CREATE TABLE Partiti(
    Codice CHAR(18) NOT NULL PRIMARY KEY,
    NomePartito CHAR(200),
    Coalizione CHAR(200)
);

CREATE TABLE Candidati(
    CPartito CHAR(18),
    FOREIGN KEY (CPartito) REFERENCES Partiti(Codice),
    Citta CHAR(100) NOT NULL PRIMARY KEY,
    NomeCand CHAR(50)
);

Create TABLE Sondaggi(
    CodPart CHAR(18),
    FOREIGN KEY (CodPart) REFERENCES Partiti(Codice),
    PercFavorevoli INT 
);