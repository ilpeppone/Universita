USE Parco_divertimenti;

CREATE TABLE Persona(
    CF CHAR(18) NOT NULL PRIMARY KEY,
    Nome CHAR (30),
    Cognome CHAR (30),
    Data_Nascita DATE,
    Via CHAR(200),
    Citta CHAR (100),
    Cap CHAR (5),
    Provincia CHAR(100)
);

CREATE TABLE Giostra(
    Numero_Serie INT NOT NULL PRIMARY KEY,
    Capienza INT,
    CF_Prop CHAR(18),
    FOREIGN KEY (CF_Prop) REFERENCES Persona (CF),
    Data_Fabbricazione DATE
);

CREATE TABLE Biglietto(
    ID CHAR(20) NOT NULL PRIMARY KEY,
    Tipo CHAR(50),
    Importo DECIMAL(10,2),
    CF_Acq CHAR(18),
    FOREIGN KEY (CF_Acq) REFERENCES Persona (CF),
    NS_Giostra INT,
    FOREIGN KEY (NS_Giostra) REFERENCES Giostra(Numero_Serie)
);

