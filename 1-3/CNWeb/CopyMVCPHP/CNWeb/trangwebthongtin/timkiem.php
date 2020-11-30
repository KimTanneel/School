<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form action="xulitimkiem.php" method="GET">
        <h1>Tìm kiếm thông tin Nhân Viên</h1>
        <input id="idvn" type="radio" name="option" value="IDNV"  checked>
        <label >IDNV</label>
        <input id="hoten" type="radio" name="option" value="hoten">
        <label >Hoten</label>
        <input id="diachi" type="radio" name="option" value="Serach">
        <label >DiaChi</label>
        </br>
        <input type="text" name="timkiem">
        <input type="submit" value="Search">
    </form>
    <!-- <a href="xemthongtinNVPB?IDPB='.$row['IDPB']'"></a>
    <a href='xemthongtinNVPB?IDPB=".$row["IDPB"]"'></a> -->
</body>
</html> 