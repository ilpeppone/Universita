USE Ecommerce;

-- 1)  Aumentare del 10% il prezzo di tutti i prodotti che costano più di 100.00 euro e aumentare del 15% tutti gli altri

UPDATE Prodotto
SET prezzo = CASE
    WHEN prezzo > 100.00 THEN prezzo * 1.10
    ELSE prezzo * 1.15
    END;

-- 2) Eliminare la colonna ‘status’ dalla tabella ordine
ALTER TABLE Ordine
DROP COLUMN stato;

-- 3)  Aggiornare le quantità dei prodotti in magazzino aggiungendo 1 prodotto ad ognuno
UPDATE Prodotto
SET quantita = quantita + 1;

-- 4)  Aggiungere la categoria ‘Abbigliamento’ all’articolo ‘smartwatch’
INSERT INTO Categoria_prod (nome,categoria)
VALUES ('Smartwatch','Abbigliamento');

-- 5) Restituire tutti gli ordini con i dati degli utenti che lo hanno effettuato e i dati della spedizione
SELECT O.codice , O.data_ordine, U.username, U.nome, U.cognome, S.data_di_sped, S.indirizzo
FROM Utente U
JOIN Ordine O ON U.username = O.username_utente
JOIN Spedizione S ON O.codice = S.codice ;

-- 6)  Recupera tutte le distinte categorie e il numero di prodotti appartenenti presenti ordinandole alfabeticamente
SELECT C.categoria,COUNT(P.nome) AS Numero_prodotti
FROM Categoria_prod C
JOIN Prodotto P ON C.nome = P.nome
GROUP BY C.categoria
ORDER BY categoria;
-- 7) Restituire per ogni utente il numero di ordini che ha effettuato (se sono zero deve essere zero), ordina il risultato dall’utente con più ordini
SELECT U.nome,COUNT(O.username_utente) AS Numero_ordini
FROM Utente U 
LEFT JOIN Ordine O ON U.username = O.username_utente
GROUP BY U.nome
ORDER BY Numero_ordini DESC;
-- 8)  Calcolare il prezzo medio dei prodotti
SELECT AVG(prezzo)
FROM Prodotto;
-- 9)  Calcolare la spesa media per ognuno degli ordini presenti
SELECT C.codice, SUM(P.prezzo * C.quantita) / COUNT(C.codice) AS spesa_media
FROM Composto C 
JOIN Prodotto P ON C.nome = P.nome
GROUP BY C.codice;
-- 10) Calcolare il numero di articoli presente in ogni ordine
SELECT codice,SUM(quantita) AS numero_articoli
FROM Composto
GROUP BY codice;
-- 11) Calcolare il numero medio di articoli presenti in ogni ordine
SELECT AVG(numero_articoli) AS numero_medio_articoli
FROM (
    SELECT codice, SUM(quantita) AS numero_articoli
    FROM Composto
    GROUP BY codice;
) AS ordine_articoli;
-- 12) Calcolare per ogni prodotto quante volte questo è stato ordinato e disporli in ordine decrescente
SELECT nome,SUM(quantita) AS totale_quantita
FROM Composto 
GROUP BY nome
ORDER BY totale_quantita DESC;
-- 13) Trovare il prodotto (o i prodotti) che sono stati venduti maggiormente
SELECT nome, totale_quantita
FROM (
    SELECT nome, SUM(quantita) AS totale_quantita
    FROM Composto
    GROUP BY nome
) AS QuantitaProdotti
WHERE totale_quantita = (
    SELECT MAX(totale_quantita)
    FROM (
        SELECT SUM(quantita) AS totale_quantita
        FROM Composto
        GROUP BY nome
    ) AS MaxQuantita
);


