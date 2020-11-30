<%@ page import="model.Bean.Wife" %>
<%@ page import="java.util.ArrayList" %><%--
  Created by IntelliJ IDEA.
  User: ADMIN
  Date: 11/20/2020
  Time: 9:12 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>JSP Page</title>
    <link href="../bootstrap.min.css">
</head>
<body>
<table class="table table-hover" >
    <tr>
        <th>Tên</th>
        <th>Địa chỉ</th>
        <th>Tình trạng</th>

    </tr>
    <%
        ArrayList<Wife> wifeArray = (ArrayList<Wife>)request.getAttribute("wifeArray");
        for (int i =0;i<wifeArray.size();i++){
    %>
    <tr>
        <td><%=wifeArray.get(i).getName()%></td>
        <td><%=wifeArray.get(i).getAddress()%></td>
        <td><%=wifeArray.get(i).isAlive()%></td>
    </tr>
    <%}%>
</table>
</body>
</html>

