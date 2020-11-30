<?php 
$link = mysqli_connect ('localhost','root') or die('Could not connect');
$db_selected = mysqli_select_db($link,'DULIEU2');
$rs = mysqli_query($link,'SELECT * FROM nhanvien');
echo '<table border="1" width="100%">';
echo "<h1 style='text-align: center;'> Dữ liệu bảng nhân viên</h1>";
echo '<TR><TH>IDNV</TH><TH>Ho ten</TH><TH>IDPB</TH><TH>Dia chi</TH></TR>';
//hien thi tung bang
while ($row = mysqli_fetch_array($rs,MYSQLI_BOTH)){
    echo '<TR>
        <TD>'.$row['IDNV'].'</TD>
        <TD>'.$row['hoten'].'</TD>
        <TD>'.$row['IDPB'].'</TD>
        <TD>'.$row['Diachi'].'</TD>
    </TR>';
}
echo'</TABLE>';
mysqli_free_result($rs);
mysqli_close($link);

?>
