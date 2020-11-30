<!-- <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body> -->
   
    <?php
        include("../header.php");
        echo "<div class='titles'>
        <h2>Danh Sách Sinh viên</h2>
        </div>";
        echo "
        <table class='table' boder ='1' width='100%'>
            <tr>
                <th><center>Mã Sinh Viên</th>
                <th><center>Tên Sinh Viên</th>
                <th><center>Tuổi</th>
                <th><center>Trường Đại học</th>
                <th><center>Chỉnh Sửa</th>
            </tr>
        "; 
        for($i=0;$i<=sizeof($studentList)-1;$i++){
            echo ("<tr>
                            <td><center>".$studentList[$i]->id."</td>
                            <td><center>".$studentList[$i]->name."</td>
                            <td><center>".$studentList[$i]->age."</td>
                            <td><center>".$studentList[$i]->university."</td>
                            <td><center><a href='?stid=".$studentList[$i]->id."&choice=2'>xxx</a></td>
            </tr>");
        }
        echo ("</table>");
        // echo $content;
    ?>  
    </br>
    <p><a href="http://localhost/MVC/index/index.php">Home Page</a></p>

</body>
</html>