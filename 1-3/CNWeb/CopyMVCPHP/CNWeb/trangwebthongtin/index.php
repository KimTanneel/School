<!DOCTYPE html>
<html>
<head>
<title>Ví dụ tao Frame trong HTML</title>
</head>
<frameset rows="10%,80%,10%">
   <frame name="top" src="./form1.php" />
   <frameset cols="25%,50%,25%">
    <frame name="left" src="./form2.php" />
    <frame name="center" src="./login.php" />
    <frame name="right" src="./form4.php" />
 </frameset>
   <frame name="bottom" src="./form5.php" />
</frameset>
</html>