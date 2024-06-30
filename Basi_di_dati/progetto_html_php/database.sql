CREATE SCHEMA IF NOT EXISTS Musei_Tate;
USE Musei_Tate;
CREATE TABLE ARTISTI(
    id INT NOT NULL PRIMARY KEY,
    nome VARCHAR (120),
    genere VARCHAR(6),
    anno_nascita INT,
    anno_morte  INT,
    luogo_nascita VARCHAR(44),
    luogo_morte VARCHAR(43),
    indirizzo_url VARCHAR(131)
);
CREATE TABLE OPERE(
    id INT NOT NULL PRIMARY KEY,
    accession_number CHAR(7),
    ruoloartista VARCHAR(24),
    id_artista INT,
    FOREIGN KEY (id_artista) REFERENCES ARTISTI(id),
    titolo VARCHAR(320),
    dataTesto VARCHAR(75),
    media VARCHAR(120),
    crediti VARCHAR(821),
    anno INT,
    anno_acquisizione INT,
    dimensioni VARCHAR(248),
    inscription CHAR(14),
    thumbnailCopyright VARCHAR(984),
    thumbnailUrl VARCHAR(57),
    indirizzo_url VARCHAR(134)
);