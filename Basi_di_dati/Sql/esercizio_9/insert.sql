USE ECOMMERCE;

INSERT INTO UTENTE(USERNAME,NOME,COGNOME,EMAIL) VALUES
('alice123', 'Alice', 'Rossi', 'alice.rossi@email.com'),
('bob456', 'Bob', 'Bianchi', 'bob.bianchi@email.com'),
('carla789', 'Carla', 'Verdi', 'carla.verdi@email.com'),
('davide10', 'Davide', 'Neri', 'davide.neri@email.com'),
('emma22', 'Emma', 'Gialli', 'emma.gialli@email.com'),
('francesco5', 'Francesco', 'Viola', 'francesco.viola@email.com'),
('giulia88', 'Giulia', 'Marroni', 'giulia.marroni@email.com'),
('hannah42', 'Hannah', 'Blu', 'hannah.blu@email.com'),
('igor77', 'Igor', 'Arancioni', 'igor.arancioni@email.com'),
('jenny90', 'Jenny', 'Grigi', 'jenny.grigi@email.com');

INSERT INTO ORDINE(CODICE,DATA_ORDINE,STATO,USERNAME_UTENTE) VALUE
(1, '2022-01-15', 'In attesa di pagamento', 'alice123'),
(2, '2022-02-03', 'In elaborazione', 'bob456'),
(3, '2022-02-14', 'Spedito', 'carla789'),
(4, '2022-03-01', 'Consegnato', 'davide10'),
(5, '2022-03-10', 'In attesa di pagamento', 'emma22'),
(6, '2022-03-18', 'In elaborazione', 'emma22');

INSERT INTO PRODOTTO(NOME,PREZZO,QUANTITA) VALUE
('Maglietta', 12.99, 150),
('Scarpe da ginnastica', 79.99, 50),
('Lampada', 24.99, 70),
('Abito elegante', 129.99, 30),
('Zaino', 29.99, 100),
('Scrivania', 500.00, 20),
('Orecchini pendenti', 14.99, 0),
('Smartwatch', 149.99, 40);

INSERT INTO CATEGORIA_PROD (NOME,CATEGORIA) VALUE
('Maglietta', 'Abbigliamento'),
('Scarpe da ginnastica', 'Abbigliamento' ),
('Scarpe da ginnastica', 'Sport'),
('Abito elegante', 'Abbigliamento'),
('Abito elegante', 'Festivo'),
('Lampada', 'Casa'),
('Lampada', 'Luci'),
('Lampada', 'Ufficio'),
('Smartwatch', 'Elettronica');

INSERT INTO COMPOSTO(NOME,CODICE,QUANTITA) VALUE
('Maglietta', 1, 2),
('Scarpe da ginnastica', 1, 1),
('Abito elegante', 1, 2),
('Lampada', 1, 1),
('Lampada', 2,3),
('Zaino', 2,1),
('Orecchini pendenti', 2,2),
('Orecchini pendenti', 3,2),
('Maglietta', 3,5),
('Smartwatch', 3,8),
('Maglietta', 4,10),
('Smartwatch', 4,1),
('Zaino', 5,1),
('Scrivania', 6,1);

INSERT INTO SPEDIZIONE (CODICE,DATA_DI_SPED,INDIRIZZO) VALUE
(1, '2022-01-20', 'Via Roma 1, Milano'),
(2, '2022-02-05', 'Via Verdi 3, Roma'),
(3, '2022-02-18', 'Via dei Mille 8, Firenze'),
(4, '2022-03-03', 'Corso Garibaldi 12, Torino'),
(5, '2022-03-12', 'Piazza del Popolo 7, Napoli'),
(6, '2022-03-20', 'Via Nazionale 22, Venezia');

