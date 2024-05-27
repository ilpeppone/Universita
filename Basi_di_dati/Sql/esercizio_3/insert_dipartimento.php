<?php

    include_once('connessione.php');

    $NOME_D 	= $_POST['NOME_D'];
	$NUMERO_D 	= $_POST['NUMERO_D'];
	$SSN_DIR		= $_POST['SSN_DIR'];
	$DATA_INIZIO_DIR	= $_POST['DATA_INIZIO_DIR'];

    $check_query = "SELECT SSN FROM IMPIEGATO WHERE SSN = '$SSN_DIR'";
    $check_result = mysqli_query($link, $check_query);

    if (mysqli_num_rows($check_result) > 0) {
        // Se esiste, inserisci il dipartimento
        $sql = "INSERT INTO DIPARTIMENTO (NOME_D, NUMERO_D, SSN_DIR, DATA_INIZIO_DIR)
                VALUES ('$NOME_D', '$NUMERO_D', '$SSN_DIR', '$DATA_INIZIO_DIR')";

        $query = mysqli_query($link, $sql);

        if (!$query) {
            echo "Si è verificato un errore: " . mysqli_error($link);
            exit;
        } else {
            echo "<h1>Dipartimento $NOME_D inserito con successo</h1>";
        }
    } else {
        echo "<h1>Errore: Il SSN_DIR specificato non esiste nella tabella IMPIEGATO.</h1>";
    }
        

?>
<html lang="it">
    
    <head>
        <meta charset="utf-8">
		        
		<title>Esempio HTML + PHP</title>
		
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">

		<style>
			body {
				max-width: 1200px;
			}
		</style>
    </head>

    <body>
		<p>Ho inserito il nuovo dipartimento <?php echo $NOME_D; ?></p>
		<?php $stampa="SELECT NOME_D , NUMERO_D, SSN_DIR, DATA_INIZIO_DIR  FROM dipartimento";
		$result = $link->query($stampa);
		echo "<table>";
		if ($result->num_rows>0){
			while ($row= $result->fetch_assoc()){
				echo "<tr>";
				echo "<td>" . $row["NOME_D"] . "</td><td>" . $row["NUMERO_D"] . "</td><td>"
				. $row["SSN_DIR"] . "</td><td>" . $row["DATA_INIZIO_DIR"] . "</td>" ;
				echo "</tr>";
			}
		}
		echo "</table>";
		mysqli_close($link);
		?>
		
    </body>

</html>

