<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Ad board</title>
</head>
<body>
<form action="Login" method="post">
    <label for="username">Username:</label>
    <input type="text" name="username" id="username" required>
    <br>
    <label for="password">Password:</label>
    <input type="password" name="password" id="password" required>
    <br>
    <button type="submit">Login</button>
</form>



<% if (request.getParameter("error") != null) { %>
<p style="color: red;">Incorrect password or login</p>
<% } %>

<a href="/lab15">Back to the main page</a>
</body>
</html>
