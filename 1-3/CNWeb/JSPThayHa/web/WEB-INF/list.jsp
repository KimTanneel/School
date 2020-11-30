<%@ page import="model.Bean.Wife" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.List" %><%--
  Created by IntelliJ IDEA.
  User: ADMIN
  Date: 11/24/2020
  Time: 7:27 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
    <style>
    <%@include file="bootstrap.min.css" %>
    </style>
</head>
<body>
<div>
        <%
            String s = (String)session.getAttribute("user");
            s= "Hello "+s;
        %>
    <div><h5><%=s%></h5></div>

    <table class="table table-hover">
        <tr>
            <th>Name</th>
            <th>Address</th>
            <th>Alive</th>
            <th>Edit</th>
            <th>Delete</th>
        </tr>

        <%
            List<Wife> listWife = (ArrayList<Wife>)request.getAttribute("listWife");
            for(int i =0;i<listWife.size();i++){

            %>
            <tr>
                <td><%=listWife.get(i).getName()%></td>
                <td><%=listWife.get(i).getAddress()%></td>
                <td><%=listWife.get(i).isAlive()%></td>
                <td>
                    <a href="/wife?action=edit&name=<%=listWife.get(i).getName()%>">Edit</a>
                </td>
                <td>
                    <a href="/wife?action=delete&name=<%=listWife.get(i).getName()%>">Delete</a>
                </td>
            </tr>

        <%
            }
        %>

    </table>
</div>
    <div>
        <button class="btn btn-outline-primary">
            <a href="/wife?action=create">add new</a>
        </button>
    </div>

</body>
</html>
