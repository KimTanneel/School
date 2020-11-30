<?php
    $hoten = $_REQUEST{'hoten'};
    $idpb =$_REQUEST{'idpb'};
    $diachi=$_REQUEST{'diachi'};
    $idnv=$_REQUEST{'idnv'};
    echo $idnv;
    echo $diachi;

    $link = mysqli_connect ('localhost','root') or die('Could not connect');
    $db_selected = mysqli_select_db($link,'DULIEU2');
    $sql = "update nhanvien set hoten ='{$hoten}',idpb={$idpb},diachi='{$diachi}'  where IDNV= ".strval($idnv); 
    $result = mysqli_query($link,$sql);
    header("Location: http://localhost/cnweb/trangwebthongtin/xemthongtinNV.php");
?>