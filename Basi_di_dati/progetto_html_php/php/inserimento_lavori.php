<!DOCTYPE html>
<html>
    <head>
        
        <meta charset="utf-8">
		        
		<title>Inserimento_lavori</title>
		
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">

		<style>
			body {
				max-width: 1200px;
			}
		</style>
    </head>
    <body>
        <?php
            include_once 'connessione.php';
            // Percorso del file CSV dei lavori
            $csv_file_lavori = "/home/peppe/Progetto_base_dati/lavori_puliti.csv"; // Inserisci il percorso corretto del tuo file CSV

            // disabilito il controllo delle chiavi esterne
            $conn->query("SET FOREIGN_KEY_CHECKS = 0");

            // Apre il file CSV dei lavori
            if (($handle = fopen($csv_file_lavori, "r")) !== FALSE) {
                fgetcsv($handle);//legge e scarta la prima riga
                // Itera sulle righe del file CSV
                while (($data = fgetcsv($handle)) !== FALSE) {
                    $id = $data[0];
                    $accession_number = $conn->real_escape_string($data[1]); // se un ' apostrofo ' è presente nella stringa, viene trasformato in \' prima di essere utilizzato in una query SQL
                    $artistRole = $conn->real_escape_string($data[2]);
                    $artistId = $data[3];
                    $title = $conn->real_escape_string($data[4]);
                    $dateText = $conn->real_escape_string($data[5]);
                    $medium = $conn->real_escape_string($data[6]);
                    $creditLine = $conn->real_escape_string($data[7]);
                    $year = $data[8];
                    $acquisitionYear = $data[9];
                    $dimensions = $conn->real_escape_string($data[10]);
                    $inscription = $conn->real_escape_string($data[11]);
                    $thumbnailCopyright = $conn->real_escape_string($data[12]);
                    $thumbnailUrl = $conn->real_escape_string($data[13]);
                    $url = $conn->real_escape_string($data[14]);
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

            // riabilitazione del controllo delle chiavi esterne
            $conn->query("SET FOREIGN_KEY_CHECKS = 1");

            // Chiudi la connessione al database
            $conn->close();
        ?>
    </body>
</html>

