<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <div>
        <h2>Danh Sách Sinh viên</h2>
    </div>
    <?php
        include_once("../header.php");
        for($i=0;$i<=sizeof($studentList)-1;$i++){
            echo "<p>".$studentList[$i]->id.".<a href='?stid=".$studentList[$i]->id."&choice=1'>".$studentList[$i]->name."</a>,</p>";
        }
        
    ?>  
    </br>
    <p><a href="http://localhost/MVC/index/index.php">Home Page</a></p>
</body>
</html>