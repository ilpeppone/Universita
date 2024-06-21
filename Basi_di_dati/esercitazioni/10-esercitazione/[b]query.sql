USE Centro_medico;

INSERT INTO Medico
VALUES
    (1, 'Mario', 'Rossi', 'mario.rossi@centromedico.it'),
	(2, 'Laura', 'Bianchi', 'laura.bianchi@centromedico.it'),
	(3, 'Giovanni', 'Verdi', 'giovanni.verdi@centromedico.it'),
	(4, 'Marco', 'Neri', 'marco.neri@centromedico.it'),
	(5, 'Silvia', 'Grasso', 'silvia.grasso@centromedico.it'),
	(6, 'Sarah', 'Giri', 'sarah.giri@centromedico.it'),
	(7, 'Eli', 'Rossi', 'eli.rossi@centromedico.it');

INSERT INTO Specializzazione 
VALUES
    (1, 'Cardiologia'),
	(2, 'Ginecologia'),
	(3, 'Ortopedia'),
	(4, 'Pediatria'),
	(5, 'Psicologia Clinica');

INSERT INTO Medico_specializzazione
VALUES
    (1, 1),
	(1, 3),
	(2, 2),
	(2, 4),
	(3, 1),
	(4, 3),
	(5, 5);

INSERT INTO Paziente
VALUES
    (1, 'Marco', 'Rossi', '1990-05-10'),
	(2, 'Laura', 'Bianchi', '1985-11-23'),
	(3, 'Giovanni', 'Verdi', '1978-07-15'),
	(4, 'Silvia', 'Grasso', '2000-02-18'),
	(5, 'Marco', 'Neri', '1982-09-01');

INSERT INTO Visita
VALUES 
    (1, 1, 1, '2023-03-01'),
	(2, 2, 2, '2023-03-02'),
	(3, 3, 3, '2023-03-03'),
	(4, 4, 4, '2023-03-04'),
	(5, 5, 5, '2023-05-18'),
	(6, 1, 5, '2023-05-18'),
	(7, 2, 5, '2023-05-18'),
	(8, 2, 5, '2023-05-18'),
	(9, 2, 1, '2023-05-18'),
	(10, 4, 1, '2023-05-18'),
	(11, 5, 5, '2023-05-18');
