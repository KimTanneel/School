<?php
    $idpb = $_REQUEST['IDPB'];
    $link = mysqli_connect ('localhost','root') or die('Could not connect');
    $db_selected = mysqli_select_db($link,'DULIEU2');
    $sql='Select * from nhanvien where IDPB ='.$idpb;
    $result = mysqli_query($link,$sql);
    echo '<table border = "1" width = "100%">';
	echo '<caption>DỮ LIỆU PHÒNG BAN </caption>';
	echo '<tr> <th> Mã Nhân Viên </th>
			<th>Họ Tên </th>
			<th>Mã Phòng Ban</th>
			<th>Địa Chỉ</th>
			<th>Sửa đổi</th>
			</tr>';
	while ($row = mysqli_fetch_array($result)) {
		$idnv = $row{"IDNV"};
		$hoten = $row{"hoten"};
		$idpb = $row{"IDPB"};
		$diachi = $row{"Diachi"};
		echo "<tr> <td><center>{$idnv}</td>
			<td><center>$hoten</td>
			<td><center>$idpb</td>
			<td><center>$diachi</td>
			<td><center><a href='updateNV.php?IDNV=".$idnv."'>xxx</a></td>
			</tr>";
			
    }
?>
