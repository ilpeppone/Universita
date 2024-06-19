USE Elezioni;

-- Partiti

INSERT INTO Partiti(Codice,NomePartito,Coalizione)
VALUES ('P001','Partito Democratico','Centrosinistra');

INSERT INTO Partiti(Codice,NomePartito,Coalizione)
VALUES ('P002','Lega Nord','Centrodestra');

INSERT INTO Partiti(Codice,NomePartito,Coalizione)
VALUES ('P003','Movimento 5 Stelle','Movimenti');

INSERT INTO Partiti(Codice,NomePartito,Coalizione)
VALUES ('P004','Forza Italia','Centrodestra');

-- Candidati

INSERT INTO Candidati(CPartito,Citta,NomeCand)
VALUES ('P001','Roma','Mario Rossi');

INSERT INTO Candidati(CPartito,Citta,NomeCand)
VALUES('P002','Milano','Anna Verdi');

INSERT INTO Candidati(CPartito,Citta,NomeCand)
VALUES('P003','Napoli','Giulia Neri');

-- Sondaggi

INSERT INTO Sondaggi(CodPart,PercFavorevoli)
VALUES ('P001', 45);

INSERT INTO Sondaggi(CodPart,PercFavorevoli)
VALUES ('P002', 38);

INSERT INTO Sondaggi(CodPart,PercFavorevoli)
VALUES ('P003', 52);

INSERT INTO Sondaggi(CodPart,PercFavorevoli)
VALUES ('P004', 42);



-- prove
 
INSERT INTO Partiti(Codice,NomePartito,Coalizione)
VALUES ('A13','Peppone4President','Destra');

INSERT INTO Sondaggi(CodPart,PercFavorevoli)
VALUES ('A13', 30);

INSERT INTO Candidati(CPartito,Citta,NomeCand)
VALUES('A13','Ferrara','Rossi');