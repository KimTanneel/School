<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="./MVC/bootstrap.min.css">
</head>
<body>
    <h2>Chi Tiết Sinh Viên</h2>
    <?php
        // echo $student;
        echo "<p>Name: <b>".$student->name."</b></p>";
        echo "<p>Age: ".$student->age."</p>";
        echo "<p> University: ".$student->university."</p><br>";
    ?>
    <p>
        <a href="javascript:history.back()">Back</a>
    </p>
</body>
</html>