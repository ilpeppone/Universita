<?php
    include_once 'connessione.php';
    // Percorso del file CSV degli artisti
    $csv_file_artisti = "/home/peppe/Progetto_base_dati/artisti_puliti.csv"; // Inserisci il percorso corretto del tuo file CSV

    // Apre il file CSV degli artisti
    if (($handle = fopen($csv_file_artisti, "r")) !== FALSE) {
        // Itera sulle righe del file CSV
        while (($data = fgetcsv($handle)) !== FALSE) {
            $id = $data[0];
            $name = $data[1];
            $gender = $data[2];
            $yearOfBirth = $data[3];
            $yearOfDeath = $data[4];
            $placeOfBirth = $data[5];
            $placeOfDeath = $data[6];
            $url = $data[7];
            // Query di inserimento degli artisti
            $sql = "INSERT INTO ARTISTI (id, nome, genere, anno_nascita, anno_morte, luogo_nascita, luogo_morte, indirizzo_url) 
                    VALUES ($id, '$name', '$gender', $yearOfBirth, $yearOfDeath, '$placeOfBirth', '$placeOfDeath', '$url')";

            // Esegui la query di inserimento
            if ($conn->query($sql) === TRUE) {
                echo "Record degli artisti inserito con successo<br>";
            } else {
                echo "Errore nell'inserimento del record degli artisti: " . $conn->error . "<br>";
            }
        }

        // Chiudi il file CSV degli artisti
        fclose($handle);
    } else {
        echo "Errore nell'apertura del file CSV degli artisti";
    }

    // Chiudi la connessione al database
    $conn->close();
?>