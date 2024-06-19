USE Lavoratori;
-- a. Trovare il nome delle persone con cognome 'Rossi'.  
SELECT CodFisc, Nome, Cognome
FROM Impiegato
    WHERE Cognome = 'Rossi';
-- alternativa
SELECT *
FROM Impiegato
    WHERE Cognome = 'Rossi';
-- b. Trovare i nomi dei dipartimenti in cui lavorano gli impiegati che stanno sul progetto 245. 
SELECT NomeD
FROM Dipartimento
JOIN Impiegato ON Dipartimento.CodD = Impiegato.Dip
JOIN Lavora_Su ON Impiegato.CodFisc = Lavora_Su.Imp
WHERE Lavora_Su.Prog = 245;
-- c. Per ogni progetto in cui lavorano almeno due impiegati, si recuperi il numero del progetto e il nome del progetto.
SELECT CodP,NomeP
FROM Progetto 
JOIN Lavora_Su ON Progetto.CodP = Lavora_Su.Prog
GROUP BY CodP,NomeP
HAVING COUNT(DISTINCT Lavora_Su.Imp) >= 2;
--d. Trovare il nome e cognome delle persone con recapito '011 6706733'   
SELECT Nome,Cognome
FROM Impiegato
WHERE Impiegato.Recapito = '011 6706733';
