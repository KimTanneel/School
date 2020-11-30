<?php 
     $link = mysqli_connect ('localhost','root') or die('Could not connect');
     $db_selected = mysqli_select_db($link,'DULIEU2');
	$sql='Select * from phongban';
    $result=mysqli_query($link,$sql);
    //   echo " <a href='http://localhost:8080/CNWeb/16_10_2020/BTVN/timkiemNV.php?data=1'>Click here</a>";
	echo '<table border = "1" width = "100%">';
	echo '<caption>Dữ liệu Phòng Ban </caption>';
	echo '<tr> <th> Mã Phòng Ban </th>
			<th>Tên Phòng Ban </th>
			<th>Mô tả</th>
			<th>Chi tiết</th>
			</tr>';
	while ($row = mysqli_fetch_array($result,MYSQLI_BOTH)) {
        $idpb = $row{"IDPB"};
		$tenpb = $row{"Tenpb"};
		$mota = $row{"Mota"};
		echo var_dump($row{"IDPB"});
		echo "<tr> <td><center>$idpb</td>
			<td><center>$tenpb</td>
			<td><center>$mota</td>
			<td><center><a href='xemthongtinNVPB.php?IDPB=$idpb'>xxx</a></td>
			</tr>";
	}
	mysqli_close($link);
	// $sua = "<a href='xemthongtinNVPB.php?IDPB=' . $row['IDPB'] . ''>xxx</a>";
?>



