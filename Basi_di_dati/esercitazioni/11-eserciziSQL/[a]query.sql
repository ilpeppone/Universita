USE Azienda;

-- 00. Aggiungere alla tabella Dipartimento una nuova colonna "BUDGET", ai dipartimenti già creati deve essere assegnato un budget di 30000 
ALTER TABLE DIPARTIMENTO
ADD COLUMN BUDGET INT;

UPDATE DIPARTIMENTO
SET BUDGET = 30000;

-- 1. Aggiungere un nuovo Dipartimento con:
-- Nome: "Quality Assurance"
-- Numero: 3  
-- Direttore: Quality Assurance
-- Data inizio: 22 Maggio 1998
-- Budget: 65000 

INSERT INTO DIPARTIMENTO (NOME_D,NUMERO_D,SSN_DIR,DATA_INIZIO_DIR,BUDGET)
VALUES('Quality Assurance',3,'Quality Assurance','1998-05-22',65000);

INSERT INTO IMPIEGATO (NOME_BATT,INIZ_INT,COGNOME,SSN,DATA_N,INDIRIZZO ,SESSO,STIPENDIO,SUPER_SSN,N_D)
VALUES ('Mary','','Moore','MRRMRY65F34G876Q','1965-06-10','4562 Maccheroni, Houston, TX','F',23000,'MRRMRY65F34G876Q',3);

-- 2. Recuperare il cognome di tutti gli impiegati senza duplicati.
SELECT DISTINCT COGNOME
FROM IMPIEGATO;
-- 3. Recuperare tutte le informazioni degli impiegati con cognome Smith.
SELECT *
FROM IMPIEGATO
WHERE COGNOME = 'SMITH';
-- 4. Recuperare tutte le informazioni degli impiegati il cui cognome è "Smith" o "Borg"
SELECT *
FROM IMPIEGATO
WHERE COGNOME = 'Smith' OR COGNOME = 'Borg';
-- 5. Select all the data of IMPIEGATO that work in DIPARTIMENTO 5.
SELECT *
FROM IMPIEGATO
wHERE N_D = 5;
-- 6. Recuperare tutte le informazioni degli impiegati che lavorano nei dipartimenti 1 e 5
SELECT *
FROM IMPIEGATO
WHERE N_D = 1 OR N_D = 5;
-- 7. Recuperare tutte le informazioni degli impiegati il cui cognome inizia con "S"
SELECT *
FROM IMPIEGATO
WHERE COGNOME LIKE 'S%';
-- 8. Recuperare la somma di tutti i budget dei dipartimenti
SELECT SUM(BUDGET) AS Somma_budget
FROM DIPARTIMENTO;
-- 9. Recuperare il numero di impiegati in ogni dipartimento (Solo il numero dipartimento e il numero di impiegati)
SELECT D.NUMERO_D,COUNT(I.SSN) AS N_IMPIEGATI_DIPARTIMENTO
FROM DIPARTIMENTO D
JOIN IMPIEGATO I ON D.NUMERO_D = I.N_D
GROUP BY D.NUMERO_D;
-- 10. Recuperare tutte le informazioni degli impiegati includendo le informazioni del dipartimento in cui lavorano
SELECT *
FROM IMPIEGATO I 
JOIN DIPARTIMENTO D ON I.N_D = D.NUMERO_D;
-- 11. Recuperare il nome e il cognome di ogni impiegato, insieme al nome e al budget del dipartimento in cui lavora
SELECT I.NOME_BATT,I.COGNOME,D.NOME_D,D.BUDGET
FROM IMPIEGATO I
JOIN DIPARTIMENTO D ON I.N_D = D.NUMERO_D;
-- 12. Recuperare il nome e il cognome di ogni impiegato che lavora in un dipartimento con budget > 60000
SELECT I.NOME_BATT,I.COGNOME,D.BUDGET
FROM IMPIEGATO I
JOIN DIPARTIMENTO D ON I.N_D = D.NUMERO_D
WHERE BUDGET > 60000;
-- 13.Recuperare il nome del dipartimento con un Budget superiore alla media del budget di tutti i dipartimenti
SELECT D.NOME_D
FROM DIPARTIMENTO D
WHERE BUDGET > (
    SELECT AVG(BUDGET) AS  Media_budget
    FROM DIPARTIMENTO );
--
-- 14. Recuperare il nome dei dipartimenti che hanno più di 2 impiegat
SELECT D.NOME_D,COUNT(I.SSN) AS Numero_impiegati
FROM DIPARTIMENTO D 
JOIN IMPIEGATO I ON D.NUMERO_D = I.N_D
GROUP BY D.NOME_D
HAVING Numero_impiegati > 2;
-- 15.Ridurre il Budget di ogni dipartimento del 10% per i dipartimenti che hanno un budget maggiore di 60000
UPDATE DIPARTIMENTO
SET BUDGET = BUDGET * 0.90
WHERE BUDGET > 60000;
-- 16. Riassegnare tutti gli impiegati del dipartimento 5 al dipartimento 3.
UPDATE IMPIEGATO
SET N_D = 3
WHERE N_D =5;
-- 17. Ricavare il nome completo di tutti gli impiegati (NOME_BATT, INIZ_INT, COGNOME) e il nome del dipartimento in cui lavorano
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,D.NOME_D
FROM IMPIEGATO I 
JOIN DIPARTIMENTO D ON I.N_D = D.NUMERO_D;
-- 18. Ricavare l'elenco dei nomi completi degli impiegati e il salario in ordine crescente di salario
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,I.STIPENDIO
FROM IMPIEGATO I 
ORDER BY I.STIPENDIO ASC;
-- 19. Ricavare l'elenco dei nomi completi degli impiegati e il salario in ordine decrescente di salario
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,I.STIPENDIO
FROM IMPIEGATO I 
ORDER BY I.STIPENDIO DESC;
-- 20. Ricavare l'elenco dei nomi completi degli impiegati del dipartimento nr 5 che lavorano almeno 10 ore sul progetto "ProductX"
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,LS.ORE
FROM IMPIEGATO I 
JOIN LAVORA_SU LS ON I.SSN = LS.SSN_I
JOIN PROGETTO P ON LS.N_P = P.NUMERO_P
WHERE I.N_D = 5 AND LS.ORE > 9 AND P.NOME_P = 'ProductX';
-- 21. Ricavare l'elenco dei nomi completi degli impiegati del dipartimento nr 5 che lavorano meno di 20 ore sul progetto "ProductX"
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,LS.ORE
FROM IMPIEGATO I 
JOIN LAVORA_SU LS ON I.SSN = LS.SSN_I
JOIN PROGETTO P ON LS.N_P = P.NUMERO_P
WHERE I.N_D = 5 AND LS.ORE < 20 AND P.NOME_P = 'ProductX';
-- 22. Ricavare l'elenco dei nomi completi degli impiegati che sono direttamente supervisionati da Franklin Wong (Senza utilizzare l’SSN di Franklin Wong direttamente nella query)
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME
FROM IMPIEGATO I
WHERE ( SUPER_SSN = (
                SELECT SSN
                FROM IMPIEGATO 
                WHERE NOME_BATT = 'Franklin' AND COGNOME = 'Wong'
    )
);
-- 23. Per ogni progetto, elencare il nome del progetto e le ore che vengono impiegate da tutti gli impiegati sul progetto stesso
SELECT P.NOME_P,SUM(LS.ORE) AS SOMMA_ORE
FROM LAVORA_SU LS 
JOIN IMPIEGATO I ON LS.SSN_I = I.SSN
JOIN PROGETTO P ON LS.N_P = P.NUMERO_P
GROUP BY P.NOME_P;
-- 24. Elencare i nomi completi degli impiegati che non lavorano su alcun progetto
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME
FROM IMPIEGATO I 
LEFT JOIN LAVORA_SU LS ON I.SSN =  LS.SSN_I
WHERE LS.SSN_I IS NULL;
-- 25. Elencare per ogni dipartimento, il nome e il salario medio degli impiegati che lavorano su quel dipartimento
SELECT AVG(I.STIPENDIO) AS MEDIA_STIPENDIO,D.NOME_D
FROM DIPARTIMENTO D 
JOIN IMPIEGATO I ON D.SSN_DIR = I.SSN
GROUP BY D.NOME_D;
-- 26. Ricavare il nome e gli indirizzi di tutti gli impiegati che lavorano almeno ad un progetto di un dipartimento che ha come sede Huston
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,I.INDIRIZZO,SD.SEDE_D
FROM IMPIEGATO I 
JOIN SEDI_DIP SD ON I.N_D=SD.NUMERO_D
JOIN LAVORA_SU LS ON I.SSN = LS.SSN_I
WHERE SD.SEDE_D = 'Houston';
-- 27. Elencare i dipartimenti che non hanno impiegati
SELECT D.*,COUNT(I.SSN) AS Numero_impiegati
FROM DIPARTIMENTO D 
LEFT JOIN IMPIEGATO I ON D.NUMERO_D = I.N_D
GROUP BY D.NOME_D
HAVING Numero_impiegati = 0;
-- 28. Per ogni progetto elencare il nome del progetto ed il numero totale di ore spese su quel progetto (da tutti gli impiegati)
SELECT P.NOME_P,SUM(LS.ORE) AS ORE_TOTALI
FROM PROGETTO P 
LEFT JOIN LAVORA_SU LS ON P.NUMERO_P = LS.N_P
GROUP BY P.NOME_P;
-- 29. Recuperare il nome di tutti gli impiegati che lavorano ai progetti controllati dal dipartimento 5. 
SELECT I.NOME_BATT,I.INIZ_INT,I.COGNOME,P.NOME_P
FROM IMPIEGATO I
JOIN PROGETTO P ON P.NUM_D = I.N_D
WHERE P.NUM_D = 5;
-- 30. Recuerare la media del salario percepito dagli impiegati di sesso femminile. 
SELECT AVG(FEMMINE.STIPENDIO) AS MEDIA_STIPENDIO_FEMMINILE
FROM (
    SELECT *
    FROM IMPIEGATO
    WHERE SESSO = 'F'
) AS FEMMINE;