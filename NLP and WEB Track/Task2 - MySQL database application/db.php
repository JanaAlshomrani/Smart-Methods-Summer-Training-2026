<?php
$host     = "sql208.infinityfree.com";
$user     = "if0_42402863";
$password = "";
$dbname = "if0_42402863_personsdb";

$conn = mysqli_connect($host, $user, $password, $dbname);

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
?>


