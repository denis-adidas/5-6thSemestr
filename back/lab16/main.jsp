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
<form id="deleteForm">
    <label for="listNumber">Number of first list:</label>
    <input type="text" id="listNumber" name="listNumber" required>

    <label for="itemName">Deleted item:</label>
    <input type="text" id="itemName" name="itemName" required>

    <button type="button" onclick="deleteItem()">Delete</button>
</form>
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

    function deleteItem() {
        const listNumber = parseInt(document.getElementById("listNumber").value, 10);
        const itemName = document.getElementById("itemName").value;
        const topLevelList = document.getElementById("list");

        if (listNumber === 0) {
            topLevelList.removeChild(topLevelList.firstElementChild);
            return;
        }

        const topLevelItem = topLevelList.children[listNumber - 1];

        if (topLevelItem) {
            const nestedList = topLevelItem.querySelector(".nested");
            const listItems = nestedList.getElementsByTagName("li");

            const itemIndex = Array.from(listItems).findIndex(item => item.textContent.trim() === itemName.trim());

            if (itemIndex !== -1) {
                listItems[itemIndex].remove();
            } else {
                alert("Элемент не найден в списке.");
            }
        } else {
            alert("Список с указанным номером не существует.");
        }
    }
</script>

</body>
</html>
