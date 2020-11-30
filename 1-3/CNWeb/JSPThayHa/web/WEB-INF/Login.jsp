<%--
  Created by IntelliJ IDEA.
  User: ADMIN
  Date: 11/20/2020
  Time: 8:52 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>JSP Page</title>
    <style>
        <%@include file="bootstrap.min.css" %>
    </style>
</head>
<body>
<<form action="/login" method="post">
    USERNAME: <input type="text" name="username">
    <br>
    PASSWORD: <input type="password" name="password">
    <br><!-- comment -->
    <br><!-- comment -->
    <input type="submit" value="Login">
    <input type="reset" valueCheckLoginServlet="Reset">

</form>
</body>
</html>
