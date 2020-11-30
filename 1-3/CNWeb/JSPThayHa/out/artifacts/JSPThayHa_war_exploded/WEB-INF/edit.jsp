<%@ page import="model.Bean.Wife" %>
<%@ page import="java.util.List" %><%--
  Created by IntelliJ IDEA.
  User: ADMIN  Date: 11/24/2020
  Time: 8:15 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <style>
        <%@include file="bootstrap.min.css" %>
    </style>
</head>
<body>
<%
    Wife wife = (Wife)request.getAttribute("wife");
%>
<form action="/wife?action=edit" method="post">
    <div class="form-group">
        <label>Name</label>
        <input type="text" class="form-control" name="name" value="${wife.getName()}" readonly>
        <label>Address</label>
        <input type="text" class="form-control" name="address" value="${wife.getAddress()}">
        <label>Address</label>
        <input type="text" class="form-control" name="alive" value="${wife.isAlive()}">
        <input type="submit" value="Submit">
        <%

        %>
    </div>
</form>
</body>
</html>
