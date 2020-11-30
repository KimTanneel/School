<?php
    $idnv = $_REQUEST['IDNV'];
    $link = mysqli_connect ('localhost','root') or die('Could not connect');
    $db_selected = mysqli_select_db($link,'DULIEU2');
    $sql = 'delete from nhanvien where IDNV= '.strval($idnv); 
    $result = mysqli_query($link,$sql);
    header("Location: http://localhost/cnweb/trangwebthongtin/xemthongtinNV.php");
    
?>