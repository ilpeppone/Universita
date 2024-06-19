USE Parco_divertimenti;

-- Insert data into Persona table
INSERT INTO Persona (CF, Nome, Cognome, Data_Nascita, Via, Citta, Cap, Provincia) VALUES
('RSSMTT90A01H501Z', 'Matteo', 'Rossi', '1990-01-01', 'Via Roma 1', 'Milano', '20100', 'MI'),
('VRDLGI85B02H501X', 'Luigi', 'Verdi', '1985-02-02', 'Via Milano 2', 'Roma', '00100', 'RM'),
('BNCLRA80C03H501Y', 'Chiara', 'Bianchi', '1980-03-03', 'Via Napoli 3', 'Torino', '10100', 'TO'),
('FRNLCU75D04H501W', 'Luca', 'Ferrari', '1975-04-04', 'Via Firenze 4', 'Napoli', '80100', 'NA');

-- Insert data into Giostra table
INSERT INTO Giostra (Numero_Serie, Capienza, CF_Prop, Data_Fabbricazione) VALUES
(1, 20, 'RSSMTT90A01H501Z', '2015-06-15'),
(2, 30, 'VRDLGI85B02H501X', '2018-07-20'),
(3, 25, 'BNCLRA80C03H501Y', '2017-09-25'),
(4, 15, 'FRNLCU75D04H501W', '2016-05-10');

-- Insert data into Biglietto table
INSERT INTO Biglietto (ID, Tipo, Importo, CF_Acq, NS_Giostra) VALUES
('B001', 'Adulto', 15.00, 'RSSMTT90A01H501Z', 1),
('B002', 'Bambino', 10.00, 'VRDLGI85B02H501X', 2),
('B003', 'Adulto', 15.00, 'BNCLRA80C03H501Y', 3),
('B004', 'Adulto', 15.00, 'RSSMTT90A01H501Z', 2),
('B005', 'Bambino', 10.00, 'RSSMTT90A01H501Z', 3),
('B006', 'Adulto', 15.00, 'FRNLCU75D04H501W', 1),
('B007', 'Bambino', 10.00, 'VRDLGI85B02H501X', 3),
('B008', 'Adulto', 15.00, 'BNCLRA80C03H501Y', 4),
('B009', 'Adulto', 15.00, 'RSSMTT90A01H501Z', 4),
('B010', 'Bambino', 10.00, 'FRNLCU75D04H501W', 2);
