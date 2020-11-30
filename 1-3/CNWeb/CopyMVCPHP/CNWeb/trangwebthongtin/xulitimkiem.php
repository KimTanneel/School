<?php
		$searchInput =$_REQUEST['timkiem'];
		$option = $_REQUEST['option'];
	
    $link = mysqli_connect ('localhost','root') or die('Could not connect');
   $db_selected = mysqli_select_db($link,'DULIEU2');
//    if($_SESSION["login"]==null)
//    {
// 	 header('Location: http://localhost/cnweb/trangwebthongtin/login.html');
//    }

	switch($option){
		case "IDNV":
			 $sql = 'select * from nhanvien where IDNV= '.strval($searchInput); 
		break;
		case "hoten":
			 $sql = "select * from nhanvien where hoten like '%".$searchInput."%'";	
		 break;
 
		case "Diachi":
		$sql = "select * from nhanvien where Diachi like '%".$searchInput."%'";
		   break;
 
		default:
			 $sql = 'select * from nhanvien where IDNV= '.strval($searchInput); 
	
	 break;
	}
	
	$result = mysqli_query($link,$sql);
	echo '<table border = "1" width = "100%">';
	 echo '<caption>Dữ liệu nhân viên </caption>';
	 echo '<tr> <th> Mã Nhân Viên </th>
			 <th>Họ Tên </th>
			 <th>Mã Phòng Ban</th>
			 <th>Địa Chỉ</th></tr>';
	 while ($row = mysqli_fetch_array($result)) {
		 $idnv = $row{"IDNV"};
		 $hoten = $row{"hoten"};
		 $idpb = $row{"IDPB"};
		 $diachi = $row{"Diachi"};
		 echo "<tr> <td><center>{$idnv}</td>
			 <td><center>$hoten</td>
			 <td><center>$idpb</td>
			 <td><center>$diachi</td></tr>";
	 }
   
   
    // "xemthogntin NVPB.php?IDPB='.$row['idpb']'x"
?>