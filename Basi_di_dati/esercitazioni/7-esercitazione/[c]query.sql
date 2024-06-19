SELECT Sondaggi.Auditel
FROM Programmi
JOIN Sondaggi ON Programmi.Codice = Sondaggi.CodProg
WHERE Programmi.Codice = 'P17';

SELECT Sondaggi.Auditel
FROM Artisti
JOIN Sondaggi ON Artisti.CProgramma = Sondaggi.CodProg
WHERE Artisti.NomeArt = 'Fabio Fazio';

SELECT Programmi.NomeProgramma
FROM Programmi
JOIN Artisti ON Programmi.Codice = Artisti.CProgramma
GROUP BY Programmi.NomeProgramma
HAVING COUNT(Artisti.NomeArt) >= 2;
