<?php
//Creates new record as per request
//Connect to database
// $servername = ;        //example = localhost or 192.168.0.0
// $username = ;        //example = root
// $password = "";
// $dbname = "test";

// Create connection
$conn = new mysqli("sql300.epizy.com", "epiz_24607908", "", "test");
// Check connection
if ($conn->connect_error) {
    die("Database Connection failed: " . $conn->connect_error);
}

//Get current date and time
date_default_timezone_set('Asia/Jakarta');
$d = date("Y-m-d");
$t = date("H:i:s");
// $sql = "INSERT INTO `nodemcu_ldr_table` (Ldr, Date, Time)
//      VALUES ('300', '" . $d . "', '" . $t . "')";
// $conn->query($sql);
if (!empty($_POST['ldrvalue'])) {
    $ldrvalue = $_POST['ldrvalue'];
    $sql = "INSERT INTO `nodemcu_ldr_table` (Ldr, Date, Time)
     VALUES ('300', '" . $d . "', '" . $t . "')";
    // $sql = "INSERT INTO nodemcu_ldr_table (Ldr, Date, Time) VALUES ('".$ldrvalue."', '".$d."', '".$t."')";
    //nodemcu_ldr_table = Youre_table_name

    if ($conn->query($sql) === TRUE) {
        echo "OK";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}


$conn->close();
