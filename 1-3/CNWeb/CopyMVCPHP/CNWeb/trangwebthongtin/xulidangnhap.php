

<?php
    $username= $_POST["username"];
    $password= $_POST["password"];
    $link = mysqli_connect ('localhost','root') or die('Could not connect');
    $db_selected = mysqli_select_db($link,'DULIEU2');
    $sql = "select * from admin where username = '".$username."' And password = '".$password."'";
    $rs = mysqli_query($link,$sql);
    $rowQuery =mysqli_num_rows($rs);
    if($rowQuery>=1){
         session_start();
         
         $_SESSION["login"] = "Admin" ;
        //  echo($_SESSION["login"]); 
         header('Location: http://localhost/cnweb/trangwebthongtin/xemthongtinPB.php');
    }
    else{
        header('Location: http://localhost/cnweb/trangwebthongtin/login.html');
    }
    // echo var_dump($rs);
    // while ($row = mysqli_fetch_array($rs,MYSQLI_BOTH)){
    //     if($row['username']==$username && $row['password']==$password){
    //         header('Location: http://localhost/cnweb/trangwebthongtin/xemthongtinPB.php');
            
    //     }
        
    //     // else header('')
        
    // }

?>