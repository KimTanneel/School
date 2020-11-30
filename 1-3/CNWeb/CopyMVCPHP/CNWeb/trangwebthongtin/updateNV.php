<?php
    $idnv = $_REQUEST['IDNV'];
    $link = mysqli_connect ('localhost','root') or die('Could not connect');
    $db_selected = mysqli_select_db($link,'DULIEU2');
    $sql = 'select * from nhanvien where IDNV= '.strval($idnv); 
    $result = mysqli_query($link,$sql);
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Document</title>
</head>
<body>
    <h1>Chỉnh sửa thông tin nhân viên</h1>
    <form action="xuliupdate.php" method="GET">
      <?php  
        session_start();    
        
        if((isset($_SESSION['login']))){
            // DO NOT LOGIN WITH ADMIN
            while ($row = mysqli_fetch_array($result)) {
                $idnv = $row{"IDNV"};
                $hoten = $row{"hoten"};
                $idpb = $row{"IDPB"};
                $diachi = $row{"Diachi"};
                echo " 
                <table>
                   <tr>
                        <th>IDNV</th>
                        <th>Họ tên</th>
                        <th>IDPB</th>
                        <th>Địa chỉ</th>
                   </tr>
                   <tr>
                       <td>
                       
                           <input readonly name='idnv' value='{$idnv}' ></input>
                       </td>
                       <td>
                           <input type ='text' value ='{$hoten}' name = 'hoten'>
                       </td>
                       <td>
                           <input type ='text' value ='{$idpb}'name='idpb'>
                       </td>
                       <td>
                           <input type ='text' value ='{$diachi}' name ='diachi'>
                       </td>
                      
                   </tr>
                </table>
                ";
               }
        }
        else{
            // echo("hello");
           	header('Location: http://localhost/cnweb/trangwebthongtin/login.php');
           
        }
        
     ?>
     <input type='submit' value='submit'>
  
</body>
</html>