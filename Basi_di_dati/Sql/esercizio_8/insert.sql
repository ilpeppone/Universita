INSERT INTO CLIENTI  VALUES
  ('FRRLCI01T55F385O', 'Anna', 'Rossi','Via spade 5',null),
  ('CMNECI01T55F385P', 'Barbara', 'Franchi','Via roma 15','3320562983'),
  ('STYLCI11F15F435W', 'Claudio', 'Marchi','Via napoli 13',null),
  ('PPRLAI91Y15F435S', 'Daniele', 'Bianchi','Via cartoni 23','3399578634');
 
  INSERT INTO UFFICI  VALUES
  ('PostOne','Milano', 'Via cigni 12'),
('PosteItaliane','Milano', 'Via pesci 25'),
('SuperPoste','Ferrara', 'Via aquila 1');
 
INSERT INTO PACCHETTI VALUES
  (1, 'FRRLCI01T55F385O', 'via della torre 12', 1345, 4.56, 'PostOne'),
  (2, 'FRRLCI01T55F385O', 'via sasso 45', 1990, 2.45, 'PosteItaliane'),
  (3, 'CMNECI01T55F385P', 'via rossini 3', 2346, 13.56, 'PostOne'),
  (4, 'STYLCI11F15F435W', 'via gatti 44', 2347, 33.56, 'PostOne'),
  (5, 'CMNECI01T55F385P', 'via blu 31', 2348, 1.00, 'PosteItaliane'),
  (6, 'CMNECI01T55F385P', 'via arancia 77', 2333, 15.00, 'PostOne');
 
INSERT INTO IMPIEGATI VALUES
  ('FRRLCI01T55F398O', 'Anna', 'Ricci','2021-05-12',20000,'PostOne'),
  ('ANNKCI01T55F398F', 'Laura', 'Neri','2020-07-15',30000,'PostOne'),
  ('LLOCI03S55F398O', 'Riccardo', 'Livi','2021-05-18',60000,'PosteItaliane'),
  ('DNLLCI01T55F398P', 'Daniele', 'Baldi','2022-08-02',25000,'SuperPoste');
