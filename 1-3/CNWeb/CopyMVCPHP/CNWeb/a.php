<?php
    //Khai báo kết nối
    $link = mysqli_connect("localhost","root","") or die ("Khong the ket noi den CSDL MySQL");
    //Lựa chọn cơ sở dữ liệu demoPhp tu link
    mysqli_select_db($link,"dulieu");
    $sql = "Select * from table1";
    $result= mysqli_query($link,$sql);
    $num_rows = mysqli_num_rows($result);
    echo "$num_rows Rows\n";
    // dong ket noi mysql
    mysqli_close($link);
?>