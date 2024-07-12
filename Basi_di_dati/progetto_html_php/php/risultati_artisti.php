<!DOCTYPE html>
<html>
    <head>
        
        <meta charset="utf-8">
		        
		<title>Risultati artisti</title>
		
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">

		<style>
			body {
				max-width: 1200px;
			}
		</style>
        <script>
            function redirectTo(page) {
                location.href = page;
            }
        </script>
    </head>
    <body>
    <?php
        include_once 'connessione.php';

        // Recupero dei parametri di ricerca
        $id = isset($_GET['id']) && $_GET['id'] !== '' ? intval($_GET['id']) : null;
        $nome = isset($_GET['nome']) ? $conn->real_escape_string($_GET['nome']) : '';
        $genere = isset($_GET['genere']) ? $conn->real_escape_string($_GET['genere']) : '';
        $luogo_nascita = isset($_GET['luogo_nascita']) ? $conn->real_escape_string($_GET['luogo_nascita']) : '';
        $luogo_morte = isset($_GET['luogo_morte']) ? $conn->real_escape_string($_GET['luogo_morte']) : '';
        $anno_nascita = isset($_GET['anno_nascita']) && $_GET['anno_nascita'] !== '' ? intval($_GET['anno_nascita']) : null;
        $anno_morte = isset($_GET['anno_morte']) && $_GET['anno_morte'] !== ''? intval($_GET['anno_morte']) : null;
        $indirizzo_url = isset($_GET['indirizzo_url']) ? $conn->real_escape_string($_GET['indirizzo_url']) : '';

        $sql = "SELECT * FROM ARTISTI WHERE 1=1";

        // Verifica se tutte le variabili di ricerca sono nulle
        if ($id === null &&
            $nome === '' &&
            $genere === '' &&
            $luogo_nascita === '' &&
            $luogo_morte === '' &&
            $anno_nascita === null &&
            $anno_morte === null &&
            $indirizzo_url === '') {
            // Nessun parametro specificato: restituisce tutte le colonne
            $sql = "SELECT * FROM ARTISTI";

        } else {
            // Aggiungi le condizioni solo se ci sono parametri di ricerca specificati
            if ($id !== null) {
                $sql .= " AND id = $id";
            }
            if ($nome !== '') {
                $sql .= " AND nome LIKE '%$nome%'";
            }
            if ($genere !== '') {
                $sql .= " AND genere LIKE '%$genere%'";
            }
            if ($luogo_nascita !== '') {
                $sql .= " AND luogo_nascita LIKE '%$luogo_nascita%'";
            }
            if ($luogo_morte !== '') {
                $sql .= " AND luogo_morte LIKE '%$luogo_morte%'";
            }
            if ($anno_nascita !== null) {
                $sql .= " AND anno_nascita = $anno_nascita";
            }
            if ($anno_morte !== null) {
                $sql .= " AND anno_morte = $anno_morte";
            }
            if ($indirizzo_url !== '') {
                $sql .= " AND indirizzo_url LIKE '%$indirizzo_url%'";
            }
        }

        // Esegui la query
        $result = $conn->query($sql);
        // Dopo la costruzione della query
        echo "Query SQL: " . $sql . "<br>";
        if ($result === false) {
            echo "Errore nella query: " . $conn->error;
        } elseif ($result->num_rows > 0) {
            echo "<h2>Risultati della ricerca:</h2>";
            echo "<table>";
            echo "<tr><th>ID</th><th>Nome</th><th>Genere</th><th>Anno di Nascita</th><th>Anno di Morte</th><th>Luogo di Nascita</th><th>Luogo di Morte</th><th>URL</th></tr>";
            while ($row = $result->fetch_assoc()) {
                echo "<tr>";
                echo "<td>" . $row['id'] . "</td>";
                echo "<td>" . $row['nome'] . "</td>";
                echo "<td>" . $row['genere'] . "</td>";
                echo "<td>" . $row['anno_nascita'] . "</td>";
                echo "<td>" . $row['anno_morte'] . "</td>";
                echo "<td>" . $row['luogo_nascita'] . "</td>";
                echo "<td>" . $row['luogo_morte'] . "</td>";
                echo "<td><a href='" . $row['indirizzo_url'] . "'>" . $row['indirizzo_url'] . "</a></td>";
                echo "</tr>";
            }
            echo "</table>";
        } else {
            echo "<p>Nessun risultato trovato.</p>";
        }

        // Chiudi la connessione al database
        $conn->close();
        ?>
        <button type="button" onclick="redirectTo('index.html')">Pagina iniziale</button>
    </body>
</html>