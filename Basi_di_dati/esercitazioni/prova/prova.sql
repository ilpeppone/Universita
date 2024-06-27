USE Centro_medico;

insert into Paziente
values (7,'Riccardo','Chira','2003-09-05');

UPDATE Medico
SET email = 'mario.rossi@gmail.com'
WHERE id=1;

ALTER TABLE Visita
ADD COLUMN esito VARCHAR (30);

UPDATE Visita
SET esito = 'negativo'
WHERE esito IS NULL;

UPDATE Paziente
SET data_di_nascita = '2004-09-05'
WHERE id = 6;

SELECT M.id,M.email
FROM Medico M 
WHERE M.email LIKE '%centromedico%';

SELECT V.id_medico,COUNT(V.id_medico) AS N_pazienti
FROM Visita V
GROUP BY V.id_medico;

SELECT id_paziente
FROM Visita
WHERE data_visita LIKE '%-03-%';

SELECT id_specializzazione, COUNT(id_specializzazione) AS N_specializzazioni_medico
FROM Medico_specializzazione
GROUP BY id_specializzazione
ORDER BY N_specializzazioni_medico DESC;

SELECT P.*,M.nome AS nome_medico,M.cognome AS cognome_medico
FROM Visita V
JOIN Paziente P ON V.id_paziente = P.id
JOIN Medico M On V.id_medico = M.id;

SELECT M.*,COUNT(MS.id_specializzazione) AS N_specializzazioni
FROM Medico M
LEFT JOIN Medico_specializzazione MS ON M.id = MS.id_medico
GROUP BY M.id
HAVING N_specializzazioni = 0;