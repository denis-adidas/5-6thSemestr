<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Animal List</title>
    <style>
        .nested {
            display: none;
            margin-left: 15px;
        }

        .open::before {
            content: "-";
            margin-right: 5px;
        }

        .closed::before {
            content: "+";
            margin-right: 5px;
        }
    </style>
</head>
<body>

<ol id="list">
    <%
        Map<String, List<String>> animals = (Map<String, List<String>>) request.getAttribute("toggleList");
        for (Map.Entry<String, List<String>> entry : animals.entrySet()) {
    %>
    <li class="top-level closed" onclick="toggleList(this)">
        <%= entry.getKey() %>
        <ul class="nested">
            <% for (String animal : entry.getValue()) { %>
            <li><%= animal %></li>
            <% } %>
        </ul>
    </li>
    <% } %>
</ol>

<script>
    function toggleList(item) {
        const nestedList = item.querySelector(".nested");
        if (item.classList.contains("closed")) {
            item.classList.remove("closed");
            item.classList.add("open");
            nestedList.style.display = "block";
        } else {
            item.classList.remove("open");
            item.classList.add("closed");
            nestedList.style.display = "none";
        }
    }
</script>

</body>
</html>
