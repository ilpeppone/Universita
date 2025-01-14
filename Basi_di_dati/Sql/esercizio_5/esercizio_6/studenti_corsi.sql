CREATE DATABASE IF NOT EXISTS Universita;
USE Universita;

CREATE TABLE STUDENTE (
    NOME VARCHAR(14) NOT NULL;
    NUMERO_STUDENTE INT ;
    ANNO_CORSO INT ;
    CORSO_LAUREA VARCHAR (50);
    -- PRIMARY KEY
)

CREATE TABLE INSEGNAMENTO (
    NOME_INSEGNAMENTO VARCHAR(50);
    CODICE_INSEGNAMENTO VARCHAR(50) NOT NULL;
    ORE INT;
    DIPARTIMENTO VARCHAR (50);

)

CREATE TABLE MODULO (
    IDENTIFICATORE_MODULO INT;
    CODICE_INSEGNAMENTO VARCHAR(50);
    SEMESTRE VARCHAR(20);
    ANNO INT;
    DOCENTE VARCHAR (50);

)

CREATE TABLE VOTAZIONE (
    NUMERO_STIDENTE INT;
    IDENTIFICATORE_MODULO INT;
    VOTO CHAR;
)

CREATE TABLE PROPEDEUCITA (
    CODICE_INSEGNAMENTO VARCHAR(50);
    CODICE_PROPEDEUTICITA VARCHAR(50);
)