USE Elezioni;

-- a.Restituire la percentuale di favorevoli del partito con codice A13.   

SELECT Sondaggi.PercFavorevoli
    FROM Partiti
    JOIN Sondaggi ON Partiti.Codice = Sondaggi.CodPart
    WHERE Partiti.Codice = 'A13';

-- b. Restituire la percentuale di favorevoli del partito del candidato con nome 'Rossi'. 
SELECT Sondaggi.PercFavorevoli
    FROM Candidati
    JOIN Sondaggi ON Candidati.CPartito = Sondaggi.CodPart
    WHERE Candidati.NomeCand = 'Rossi';

-- c. Restituire i nomi dei partiti con percentuale di favorevoli del 30%.  
SELECT Partiti.NomePartito
    FROM Sondaggi
    JOIN Partiti ON Sondaggi.CodPart = Partiti.Codice
    WHERE Sondaggi.PercFavorevoli = 30;

-- d. Restituire i codici dei partiti con percentuale di favorevoli superiori al 20%.
SELECT Partiti.Codice
    FROM Sondaggi
    JOIN Partiti ON Sondaggi.CodPart = Partiti.Codice
    WHERE Sondaggi.PercFavorevoli > 40;