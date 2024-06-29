<?php
    include_once 'connessione.php';
    // Percorso del file CSV dei lavori
    $csv_file_lavori = "/home/peppe/Progetto_base_dati/lavori_puliti.csv"; // Inserisci il percorso corretto del tuo file CSV

    // Apre il file CSV dei lavori
    if (($handle = fopen($csv_file_lavori, "r")) !== FALSE) {
        // Itera sulle righe del file CSV
        while (($data = fgetcsv($handle)) !== FALSE) {
            // Query di inserimento dei lavori
            $sql = "INSERT INTO OPERE (id, accession_number, ruoloartista, id_artista, titolo, dataTesto, media, crediti, anno, anno_acquisizione, dimensioni, inscription, thumbnailCopyright, thumbnailUrl, indirizzo_url) 
                    VALUES ($id, '$accession_number', '$artistRole', $artistId, '$title', '$dateText', '$medium', '$creditLine', $year, $acquisitionYear, '$dimensions', '$inscription', '$thumbnailCopyright', '$thumbnailUrl', '$url')";

            // Esegui la query di inserimento
            if ($conn->query($sql) === TRUE) {
                echo "Record dei lavori inserito con successo<br>";
            } else {
                echo "Errore nell'inserimento del record dei lavori: " . $conn->error . "<br>";
            }
        }

        // Chiudi il file CSV dei lavori
        fclose($handle);
    } else {
        echo "Errore nell'apertura del file CSV dei lavori";
    }

    // Chiudi la connessione al database
    $conn->close();
?>