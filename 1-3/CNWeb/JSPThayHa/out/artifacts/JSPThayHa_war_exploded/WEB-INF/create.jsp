<%--
  Created by IntelliJ IDEA.
  User: ADMIN
  Date: 11/25/2020
  Time: 6:37 PM
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
    <h1>Add New Wife</h1>

    <form action="/wife?action=create" method="post">
        <div class="form-group">
            <label>Name</label>
            <input type="text" class="form-control" name="name" placeholder="name" >
            <label>Address</label>
            <input type="text" class="form-control" name="address" placeholder="address">
            <label>Address</label>
            <input type="text" class="form-control" name="alive" placeholder="alive">
            <input type="submit" value="Submit">
            <%

            %>
        </div>
    </form>
</body>
</html>
