USE Azienda;
SET foreign_key_checks = 0; -- disattiva i check 
INSERT INTO IMPIEGATO VALUES ('Peppe','','Viggiano', '174668', '2002-05-10',
	'via archita 56, Bernalda', 'M', 220.00,'653298653', '4');
SET foreign_key_checks = 1; -- attiva i check 
INSERT INTO DIPARTIMENTO VALUES ('LOGISTICO','4', '653298653', '1985-12-30');
INSERT INTO PROGETTO VALUES ('PACCHI', '9', 'BERNALDA', '4');