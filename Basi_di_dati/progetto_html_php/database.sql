CREATE SCHEMA IF NOT EXISTS Musei_Tate;
USE Musei_Tate;
CREATE TABLE ARTISTI(
    id INT NOT NULL PRIMARY KEY,
    nome VARCHAR (50),
    genere VARCHAR(20),
    anno_nascita INT,
    anno_morte  INT,
    luogo_nascita VARCHAR(100),
    luogo_morte VARCHAR(100),
    indirizzo_url VARCHAR(300)
);
CREATE TABLE OPERE(
    id INT NOT NULL PRIMARY KEY,
    accession_number CHAR(6),
    ruoloartista VARCHAR(20),
    id_artista INT,
    FOREIGN KEY (id_artista) REFERENCES ARTISTI(id),
    titolo VARCHAR(200),
    dataTesto VARCHAR(30),
    media VARCHAR(50),
    crediti VARCHAR(200),
    anno INT,
    anno_acquisizione INT,
    dimensioni VARCHAR(100),
    inscription CHAR(14),
    thumbnailCopyright VARCHAR(200),
    thumbnailUrl VARCHAR(300),
    indirizzo_url VARCHAR(300)
);