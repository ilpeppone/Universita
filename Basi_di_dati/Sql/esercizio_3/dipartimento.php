<?php

	include_once('connessione.php');

	$NOME_D 	= $_POST['NOME_D'];
	$NUMERO_D 	= $_POST['NUMERO_D'];
	$SSN_DIR		= $_POST['SSN_DIR'];
	$DATA_INIZIO_DIR	= $_POST['DATA_INIZIO_DIR'];
	
	$sql = "INSERT INTO DIPARTIMENTO 
					VALUES ('$NOME_D', '$NUMERO_D', '$SSN_DIR', 
							'$DATA_INIZIO_DIR')";
	
	$query = mysqli_query($link, $sql);

	if (!$query) {
		echo "Si è verificato un errore: " . mysqli_error($link);
		exit;
	}
	
?>

<html lang="it">
    
    <head>
        <meta charset="utf-8">
		        
		<title>Dipartimento</title>
		
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">

		<style>
			body {
				max-width: 1200px;
			}
		</style>
    </head>

    <body>
		<p>Ho inserito il nuovo dipartimento <?php echo $NOME_BATT; ?></p>
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

