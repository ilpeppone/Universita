<?php

	include_once('connessione.php');
    if (empty($_POST)) {
       
    } else {
        $NOME_D 	= $_POST['NOME_D'];
	    $NUMERO_D 	= $_POST['NUMERO_D'];
	    $SSN_DIR		= $_POST['SSN_DIR'];
	    $DATA_INIZIO_DIR	= $_POST['DATA_INIZIO_DIR'];
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
    <form action="insert_dipartimento.php" method="POST">
	<form action="insert_impiegato.php" method="POST">
			<fieldset>
				<label>NOME_D:</label>
				<input type="text" name="NOME_D">
			</fieldset>
			<fieldset>
				<label>NUMERO_D:</label>
				<input type="text" name="NUMERO_D">
			</fieldset>
			<fieldset>
				<label>SSN_DIR:</label>
				<input type="text" name="SSN_DIR">
			</fieldset>
			<fieldset>
				<label>DATA_INIZIO_DIR:</label>
				<input type="date" name="DATA_INIZIO_DIR">
            </fieldset>

			<input type="submit" value="Invia" />
		</form>	
	
		
    </body>

</html>

