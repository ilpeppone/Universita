USE Televisione;


-- Programmi

INSERT INTO Programmi(Codice, NomeProgramma, Rete, Tipologia)
VALUES ('P001','Morning Show', 1, 'Talk Show');

INSERT INTO Programmi(Codice, NomeProgramma, Rete, Tipologia)
VALUES ('P002','Evening News', 2, 'News');

INSERT INTO Programmi(Codice, NomeProgramma, Rete, Tipologia)
VALUES ('P003','Movie Night', 3, "Movie");

-- Artisti
INSERT INTO Artisti(CProgramma, NomeArt)
VALUES ('P001','John Doe');

INSERT INTO Artisti(CProgramma, NomeArt)
VALUES ('P001', 'Jane Smith');

INSERT INTO Artisti(CProgramma, NomeArt)
VALUES ('P002','Alice Johnson');

INSERT INTO Artisti(CProgramma, NomeArt)
VALUES ('P003','Michael Brown');

-- Sondaggi
INSERT INTO Sondaggi(CodProg, Auditel)
VALUES ('P001', 1500);

INSERT INTO Sondaggi(CodProg, Auditel)
VALUES ('P002', 3000);

INSERT INTO Sondaggi(CodProg, Auditel)
VALUES ('P003', 2500);