USE Uffici_postali;

-- a.Trova il peso medio, massimo, minimo e il totale dei pacchetti che partono da uffici che si trovano a Milano
SELECT  AVG(Pacchetti.peso) AS PesoMedio,
        MAX(Pacchetti.peso) AS PesoMassimo,
        MIN(Pacchetti.peso) AS PesoMinimo,
        SUM(Pacchetti.peso) AS PesoTotale
FROM Pacchetti
JOIN Uffici ON Pacchetti.Nufficio = Uffici.nome
WHERE Uffici.citta = 'Milano';

-- b.  Trova quanti pacchetti ha ogni ufficio postale (se ne ha zero deve comunque apparire ufficio postale - 0 1)
SELECT Uffici.nome,COUNT(Pacchetti.tracking_number)
FROM Uffici
LEFT JOIN 
    Pacchetti ON Uffici.nome = Pacchetti.Nufficio
GROUP BY Uffici.nome;

-- c. Trova codice fiscale, nome, cognome dei clienti con associato tracking number, peso dei pacchetti e le info degli uffici da cui partono
SELECT C.codfisc,C.nome,C.cognome,P.tracking_number,P.peso,U.nome AS Nome_Ufficio,U.citta,U.indirizzo
FROM Pacchetti P
JOIN Clienti C ON P.cf_mittente = C.codfisc
JOIN Uffici U ON P.Nufficio = U.nome;
-- d. Trova le informazioni degli impiegati che hanno iniziato a lavorare tra il 2021-01-01 e il 2021-10-01
SELECT I.nome,I.data_inizio_lavoro AS DATA_INIZIO
FROM Impiegati AS I
WHERE I.data_inizio_lavoro >= '2021-01-01' AND I.data_inizio_lavoro  <= '2021-10-01';
-- e.  Trova quanti pacchetti ha inviato ogni cliente (se ne ha zero deve comunque apparire cliente - 0), ordina il risultato per numero di pacchetti decrescente
SELECT C.codfisc,COUNT(P.cf_mittente) AS NumeroPacchettiInviati
FROM Clienti C
LEFT JOIN Pacchetti P ON C.codfisc = P.cf_mittente
GROUP BY C.codfisc
ORDER BY NumeroPacchettiInviati DESC;
-- f.   Trova nome e salario degli impiegati che lavorano nell'ufficio 'PostOne', ordinali per salario decrescente
SELECT I.nome AS Nome_Impiegato,I.salario AS Salario ,U.nome AS Nome_Ufficio
FROM Impiegati I
JOIN Uffici U ON I.Nufficio = U.nome
WHERE U.nome = 'PostOne'
ORDER BY Salario DESC;
-- g. Trova nome e indirizzo del cliente che ha spedito il maggior numero di pacchetti
SELECT C.nome,C.indirizzo,COUNT(P.cf_mittente) AS Count_pacchetti
FROM Clienti C 
JOIN Pacchetti P ON C.codfisc = P.cf_mittente
GROUP BY C.nome,C.indirizzo
HAVING
    Count_pacchetti = (
        SELECT MAX(Count_pacchetti)
        FROM (
            SELECT COUNT(P2.cf_mittente) AS Count_pacchetti
            FROM Pacchetti P2
            GROUP BY P2.cf_mittente
        ) AS subquery
    );
-- h. Trova tutti i nomi, sia dei clienti sia degli impiegati e ordinali in modo crescente
SELECT C.nome AS Nome
FROM Clienti C
UNION
SELECT I.nome AS Nome
FROM Impiegati I
ORDER BY Nome ASC;
-- i.  Trova tutte le informazioni dell'impiegato/i  con salario maggiore
SELECT *
FROM Impiegati
WHERE Impiegati.salario = (SELECT MAX (salario) FROM Impiegati);
-- j. Trova il salario medio e il numero di impiegati per ufficio e ordinali in modo decrescente rispetto al salario medio
SELECT I.Nufficio, AVG(I.salario) AS Salario_Medio ,COUNT(I.Nufficio) AS Numero_Impiegati
FROM Impiegati I
GROUP BY I.Nufficio
ORDER BY Salario_Medio DESC;
-- k. Trova quanti sono i pacchetti inviati dai clienti il cui nome termina con 'a'
SELECT C.nome, COUNT(P.cf_mittente) AS Tot_pacchetti
FROM Pacchetti P
JOIN Clienti C ON P.cf_mittente = C.codfisc
WHERE C.nome LIKE '%a'
GROUP BY C.nome;
-- l. Seleziona nome e cognome di tutti gli impiegati che lavorano nella città in cui è stato inviato il pacchetto con tracking_number 1990
SELECT I.nome,I.cognome,I.Nufficio
FROM Impiegati I 
JOIN Uffici U ON I.Nufficio = U.nome
JOIN Pacchetti P ON P.Nufficio = U.nome
WHERE P.tracking_number = 1990;
-- m. Trova nome, cognome, salario degli impiegati il cui salario maggiore di almeno 20000 rispetto a tutti gli altri
SELECT I.nome,I.cognome,I.salario
FROM Impiegati I 
WHERE I.salario > 20000 + (SELECT AVG(salario) FROM Impiegati );
