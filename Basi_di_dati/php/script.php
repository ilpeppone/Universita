<?php
    $nome = $_POST['nome'];
    $esempio_select = $_POST['esempio'];
?>

<!DOCTYPE html>
<html lang="it">
    <head>
        <meta charset= "utf-8">
        <meta name = "autore" content = "Giuseppe Viggiano">
        <meta name = "descriptor" content = "Esempio 1">
        <meta name = "keywords" content = "esempio php">

        <title> Esempio php </title>

        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">

        <style>
            body{
                max-width:1200px;
            }
        </style>
    </head>
    
    <body>
        <p> Ciao <?php echo $nome ?>, hai passato il valore <?php echo $esempio_select ?> </p>
    </body>
</html>