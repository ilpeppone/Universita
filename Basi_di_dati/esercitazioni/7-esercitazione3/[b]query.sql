USE Lavoratori;

INSERT INTO Dipartimento(CodD, NomeD, Indirizzo, Citta)
VALUES  (1, 'Informatica', 'Via Roma 1', 'Ferrara'),
        (2, 'Marketing', 'Via Milano 10', 'Ferrara');

INSERT INTO Impiegato(CodFisc, Nome, Cognome, Recapito, Dip)
VALUES  ('RSSMRA85M01H501Z', 'Mario', 'Rossi', '011 6706733', 1),
        ('VRDGPP90L11H501X', 'Giuseppe', 'Verdi', '011 6706744', 2),
        ('BNCLRA80A01H501W', 'Laura', 'Bianchi', '011 6706755', 1),
        ('MRNLGI75C01H501V', 'Luigi', 'Marino', '011 6706766', 2),
        ('RSIGNN60D01H501U', 'Gianna', 'Rossi', '011 6706777', 1);

INSERT INTO Progetto(CodP, NomeP, Budget)
VALUES  (245, 'Progetto A', 10000.00),
        (246, 'Progetto B', 20000.00),
        (247, 'Progetto C', 30000.00);

INSERT INTO Lavora_Su(Imp, Prog)
VALUES  ('RSSMRA85M01H501Z', 245),
        ('VRDGPP90L11H501X', 245),
        ('BNCLRA80A01H501W', 246),
        ('MRNLGI75C01H501V', 246),
        ('RSSMRA85M01H501Z', 247),
        ('RSIGNN60D01H501U', 247);
