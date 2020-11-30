<?php
    $idnv =$_REQUEST["idnv"];
    $hoten =$_REQUEST["hoten"];
    $idpb =$_REQUEST["idpb"];
    $diachi =$_REQUEST["diachi"];

     $link = mysqli_connect ('localhost','root') or die('Could not connect');
    $db_selected = mysqli_select_db($link,'DULIEU2');
    $sql="insert into nhanvien (hoten,IDPB,Diachi) values ('".$hoten."', '".$idpb."', '".$diachi."')";
    // INSERT INTO `nhanvien` ( hoten, IDPB, Diachi) VALUES ('Thành Vinhhhhh', '12', '150 Hà Huy Tính')
    // insert into nhanvien (hoten,IDPB,Diachi) values ('Hoang Phuc', '12', '15 Âu Cơ')
    $result = mysqli_query($link,$sql);
    header("Location: http://localhost/cnweb/trangwebthongtin/xemthongtinNV.php");
?>