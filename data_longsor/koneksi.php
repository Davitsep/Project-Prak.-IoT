<?php
$host = "localhost";
$dbname = "deteksi_longsor";
$username = "root";
$password = "";

$koneksi = mysqli_connect($host, $username, $password, $dbname);

if(mysqli_connect_errno()){
    echo 'Gagal melakukan koneksi ke Database : '.mysqli_connect_error();

}
