<?php
    $rows=[];
    $data = array(
        'Nome' => 'Mario', 
        'Cognome' => 'Rossi', 
        'Salario' => '20.000');
        
    array_push($rows, $data);
    
    // Seconda riga
    $data = [
            'Nome' => 'Alberto', 
            'Cognome' => 'Bianchi', 
            'Salario' => '21.000'
        ];
        
    array_push($rows, $data);
    
    // Terza riga
    $data = [
            'Nome' => 'Giulio', 
            'Cognome' => 'Neri', 
            'Salario' => '26.000'
        ];
        
    array_push($rows, $data);
?>
<html lang="it">
    <head>
        <meta charset="utf-8">
		<meta name="author" content="Giuseppe Viggiano" />
        <meta name="description" content="Esempio 2">
		<meta name="keywords"  content="esempio html, esempio php" />		
        
		<title>Esempio PHP</title>
		
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">

		<style>
			body {
				max-width: 1200px;
			}
		</style>
    </head>