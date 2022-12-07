<?php
require("koneksi.php");
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta http-equiv="refresh" content="5">
    <title>Log Data Longsor</title>
</head>

<body>
    <style>
        #wntable {
            border-collapse: collapse;
            width: 50%;
        }

        #wntable td,
        #wntable th {
            border: 1px solid #add;
            padding: 8px;
        }

        #wntable tr:nth-child(even) {
            background-color: #f2f2f2;
        }

        #wntable tr:hover {
            background-color: #add;
        }

        #wntable th {
            padding-top: 12px;
            padding-bottom: 12px;
            text-align: left;
            background-color: #00A8A9;
            color: white;
        }
    </style>
    <div id="cards" class="cards" align="center">
        <h1>Log Data Deteksi Longsor</h1>
        <table id="wntable">
            <tr>
                <th>No</th>
                <th>Kelembaban</th>
                <th>Kondisi</th>
                <th>Keterangan</th>
                <th>Tanggal</th>
                <th>Waktu</th>
            </tr>
            <?php
            $sql = mysqli_query($koneksi, "SELECT * FROM log_data_longsor ORDER BY id DESC");
            if (mysqli_num_rows($sql) == 0) {
                echo '<tr><td colspan="14"> Data Tidak Ada. </td></tr>';
            } else {
                $no = 1;
                while ($row = mysqli_fetch_assoc($sql)) {
                    echo '
                    <tr>
                    <td>' . $no . '</td>
                    <td>' . $row['kelembaban'] . '</td>
                    <td>' . $row['kondisi'] . '</td>
                    <td>' . $row['keterangan'] . '</td>
                    <td>' . $row['tanggal'] . '</td>
                    <td>' . $row['waktu'] . '</td>
                    </tr>
                    ';
                    $no++;
                }
            }
            ?>
        </table>
    </div>
</body>

</html>