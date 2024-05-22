<?php

	include_once('connessione.php');

	$NOME_BATT 	= $_POST['NOME_BATT'];
	$INIZ_INT 	= $_POST['INIZ_INT'];
	$COGNOME 	= $_POST['COGNOME'];
	$SSN 		= $_POST['SSN'];
	$DATA_N 	= $_POST['DATA_N'];
	$INDIRIZZO 	= $_POST['INDIRIZZO'];
	$SESSO 		= $_POST['SESSO'];
	$STIPENDIO 	= $_POST['STIPENDIO'];
	$SUPER_SSN 	= $_POST['SUPER_SSN'];
	$N_D 		= $_POST['N_D'];
	
	$sql = "INSERT INTO IMPIEGATO 
					VALUES ('$NOME_BATT', '$INIZ_INT', '$COGNOME', '$SSN', 
							'$DATA_N', '$INDIRIZZO', '$SESSO', $STIPENDIO, 
							'$SUPER_SSN', $N_D)";
	
	$query = mysqli_query($link, $sql);

	if (!$query) {
		echo "Si è verificato un errore: " . mysqli_error($link);
		exit;
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
		<p>Ho inserito il nuovo impiegato <?php echo $NOME_BATT; ?></p>
		<?php $stampa="SELECT NOME_BATT , INIZ_INT, COGNOME, SSN, DATA_N, INDIRIZZO, SESSO, STIPENDIO, SUPER_SSN  FROM impiegato";
		$result = $link->query($stampa);
		echo "<table>";
		if ($result->num_rows>0){
			while ($row= $result->fetch_assoc()){
				echo "<tr>";
				echo "<td>" . $row["NOME_BATT"] . "</td><td>" . $row["INIZ_INT"] . "</td><td>"
				. $row["COGNOME"] . "</td><td>" . $row["SSN"] . "</td><td>" . $row["DATA_N"] 
				. "</td><td>" . $row["INDIRIZZO"] . "</td><td>" . $row["SESSO"] . "</td><td>" 
				. $row["STIPENDIO"] . "</td><td>" . $row["SUPER_SSN"] . "</td>";
				echo "</tr>";
			}
		}
		echo "</table>";
		mysqli_close($link);
		?>
		
    </body>

</html>

