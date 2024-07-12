<?php
// Configurazione del database
$servername = "localhost";
$username = "peppe"; 
$password = "panecotto07@"; 
$dbname = "Musei_Tate"; 

// Connessione al database
$conn = new mysqli($servername, $username, $password, $dbname);

// Verifica la connessione
if ($conn->connect_error) {
    die("Connessione fallita: " . $conn->connect_error);
} 

?>
