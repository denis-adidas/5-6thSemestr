<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@page import="java.util.ArrayList, model.NotebookModel" %>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Notebook</title>
</head>
<body>
<h1>Notebook Entries</h1>
<ul>
    <% ArrayList<NotebookModel.Person> notebook = (ArrayList<NotebookModel.Person>) request.getAttribute("notes"); %>
    <% if (notebook != null) { %>
    <% for (NotebookModel.Person person : notebook) { %>
    <p><%= person.toString() %></p>
    <% } %>
    <% } %>
</ul>
<h2>Search results:</h2>
<ul>
    <% String searchResult = request.getParameter("searchResult"); %>
    <% if (searchResult != null && !searchResult.isEmpty()) { %>
    <% for (NotebookModel.Person person : notebook) { %>
    <% if (searchResult.equals(person.getName())) { %>
    <p><%= person.toString() %></p>
    <% } %>
    <% } %>
    <% } %>
</ul>
<form method="GET" action="${pageContext.request.contextPath}/NoteBook/number">
    Name: <input type="text" name="name">
    Phone: <input type="text" name="number">
    <input type="submit" value="add">
</form>
<br>
<form method="GET" action="${pageContext.request.contextPath}/NoteBook/searchResult">
    Name: <input type="text" name="searchResult">
    <input type="submit" value="Search">
</form>

<a href="${pageContext.request.contextPath}/NoteBook/reset">Reset</a>
</body>
</html>
