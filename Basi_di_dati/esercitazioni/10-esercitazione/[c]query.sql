USE Centro_medico;

-- 1)  Inserisci un nuovo paziente con id=6
INSERT INTO Paziente (id, nome, cognome, data_di_nascita)
VALUES 
    (6,'Giuseppe','Viggiano','2002-05-10');
-- 2)  Aggiorna la mail del dottor Mario Rossi (id=1) modificandola con: ‘mario.rossi@gmail.com’
UPDATE Medico
SET email = 'mario.rossi@gmail.com'
WHERE id=1;
-- 3) Modifica la tabella ‘visite’ aggiungendo la colonna ‘note’ con tipo VARCHAR(255)
ALTER TABLE Visita
ADD COLUMN note VARCHAR(255);
-- 4)  Fai un update alla tabella visite aggiungendo la stessa nota alle visite con id 1, 2 e 3
UPDATE Visita
SET note = 'appuntamento posticipato di un giorno'
WHERE id IN (1,2,3);
-- 5)  Fai un update per la tabella ‘pazienti’ per aggiornare la data di nascita del paziente con ID 
UPDATE Paziente
SET data_di_nascita = '1992-09-01'
WHERE id = 5;
-- 6)  Seleziona nome e cognome e mail dei medici che hanno ‘centromedico’ nella loro mail
SELECT nome,cognome,email
FROM Medico
WHERE email LIKE '%centromedico%';
-- 7)  Trova per ogni medico il numero di visite effettuate
SELECT M.id,M.nome,M.cognome,COUNT(V.id_paziente) AS Pazienti_visitati
FROM Medico M 
LEFT JOIN Visita V ON M.id = V.id_medico
GROUP BY M.id;
-- 8) Trova i pazienti che hanno effettuato visite nel mese di marzo
SELECT P.nome, P.cognome
FROM Paziente P
JOIN Visita V ON P.id = V.id_paziente
WHERE MONTH(data_visita) = 3;
-- 9) Trova per ogni specializzazione quanti medici ci sono, , ordina i risultati in modo decrescente 
SELECT S.nome,COUNT(M.id) AS Numero_medici
FROM Specializzazione S 
JOIN Medico_specializzazione MS ON S.id = MS.id_specializzazione
JOIN Medico M ON M.id = MS.id_medico
GROUP BY S.nome
ORDER BY Numero_medici DESC;
-- 10) Seleziona tutti i dati dei pazienti con le visite che hanno effettuato (se ci sono) e il nome e cognome dei medici che le hanno effettuate
SELECT P.id,P.nome,P.cognome,P.data_di_nascita,V.data_visita, M.nome AS Nome_medico ,M.cognome AS Cognome_medico
FROM Paziente P
JOIN Visita V ON P.id = V.id_paziente
JOIN Medico M ON V.id_medico = M.id;
-- 11)  Seleziona tutti i dati dei medici che non hanno specializzazioni
SELECT M.id,M.nome,M.cognome,M.email
FROM Medico M 
LEFT JOIN Medico_specializzazione MS ON M.id = MS.id_medico
WHERE MS.id_specializzazione IS NULL;
-- 12) Seleziona per ogni medico il suo numero di specializzazioni
SELECT M.*, COUNT(MS.id_specializzazione) AS Numero_specializzazioni
FROM Medico M
LEFT JOIN Medico_specializzazione MS ON M.id = MS.id_medico
GROUP BY M.id;
-- 13) Seleziona tutti i pazienti che hanno effettuato almeno 3 visite
SELECT P.*, COUNT(V.id_paziente) AS N_visite
FROM Paziente P
JOIN Visita V ON P.id = V.id_paziente
GROUP BY P.id
HAVING N_visite > 2;
-- 14) Seleziona le informazioni dei medici che hanno effettuato visite ad almeno 3 pazienti diversi
SELECT M.*,COUNT(DISTINCT V.id_paziente) AS Pazienti_diversi
FROM Medico M 
JOIN Visita V ON M.id = V.id_medico
GROUP BY M.id
HAVING Pazienti_diversi > 2;
