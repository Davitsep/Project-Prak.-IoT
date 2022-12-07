<?php

$host = "localhost";                 // host = localhost because database hosted on the same server where PHP files are hosted
$dbname = "deteksi_longsor";              // Database name
$username = "root";        // Database username
$password = "";            // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} else {
    echo "Connected to mysql database. ";
}

// Get date and time variables
date_default_timezone_set('Asia/Bangkok');  // for other timezones, refer:- https://www.php.net/manual/en/timezones.asia.php
$d = date("Y-m-d");
$t = date("H:i:s");

// If values send by NodeMCU are not empty then insert into MySQL database table
$sendval2 = $_GET["sendval2"];
if ($sendval2 == 1) {
    $kondisi = 'Hujan';
} else {
    $kondisi = 'Tidak Hujan';
}

$sendval3 = $_GET["sendval3"];
if ($sendval3 == 1) {
    $keterangan = 'Berpotensi Longsor';
} else if ($sendval3 == 2) {
    $keterangan = 'Peringatan Dini';
} else if ($sendval3 == 3) {
    $keterangan = 'Hujan';
} else if ($sendval3 == 4) {
    $keterangan = 'Normal';
}
$result = mysqli_query($conn, "INSERT INTO log_data_longsor (kelembaban, kondisi, keterangan, tanggal, waktu) VALUES ('" . $_GET["sendval"] . "','" . $kondisi . "','" . $keterangan . "', '" . $d . "', '" . $t . "')");

if (!$result) {
    die('Invalid Query: ' . mysqli_error($conn));
}
