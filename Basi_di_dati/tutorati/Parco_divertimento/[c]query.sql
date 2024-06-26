USE Parco_divertimenti;

-- Query 1

SELECT COUNT(*)
FROM Persona AS P JOIN Biglietto AS B
    ON P.CF = B.CF_Acq
WHERE Nome = 'Matteo' AND Cognome = 'Rossi' AND
    data >= 2023

-- Query 2

SELECT CF,Nome,Cognome
    FROM Giostra JOIN Persona ON CF_Prop = CF
    JOIN Biglietto ON CF = CF_Acq ;

-- Query 3

SELECT CF,Nome,Cognome
FROM Persona AS P JOIN Biglietto AS B
    ON P.CF = B.CF_Acq
    GROUP BY CF_Acq
    HAVING COUNT(*)>2;

-- Query 4

SELECT Numero_Serie,Data_Fabbricazione
FROM Giostra
ORDER BY Data_Fabbricazione ASC;

-- Query 5

SELECT CF,Nome,Cognome
FROM Persona
WHERE CF NOT IN 
    (SELECT CF_Acq
    FROM Biglietto);

-- Query 6

SELECT Numero_Serie,Capienza, COUNT(*)
FROM Giostra
    JOIN Biglietto AS B1 ON Numero_Serie = B1.NS_Giostra
    WHERE B1.data >= '2023-01-01' AND B1.data <= '2023-12-31'
    GROUP BY B1.NS_Giostra
    HAVING COUNT(*) = (
        SELECT MIN(CB_23)
        FROM (
            SELECT COUNT(*) AS CB_23
            FROM Biglietto AS B2
            WHERE B2.data >= '2023-01-01' AND B2.data <= '2023-12-31'
            GROUP BY B2.NS_Giostra
        ) AS CONTEGGI
);

-- QUERY 7

SELECT Provincia,COUNT(*)
FROM Persona
    JOIN Biglietto ON CF=CF_Acq
    GROUP BY Provincia;
