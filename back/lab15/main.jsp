<%@ page import="org.suai.lab15.AdModel" %>
<%@ page import="java.util.ArrayList" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Ad boards</title>
</head>
<body>
<h1>Ad board</h1>

<% String username = (String)session.getAttribute("username");
    if (username != null) { %>
<h2>Welcome, <%= username %>!</h2>
<a href="${pageContext.request.contextPath}/Logout">Logout</a>
<form action="/lab15/AddAd" method="post">
    <label for="adTitle">title:</label>
    <input type="text" name="adTitle" id="adTitle" required>
    <br>
    <label for="adText">text:</label>
    <textarea name="adText" id="adText" required></textarea>
    <br>
    <button type="submit">Add ad</button>
</form>
<% } else { %>
<a href="${pageContext.request.contextPath}/Login">Login</a>
<% } %>
<br>

<h2>Ads list</h2>
<% ArrayList<AdModel> ads = (ArrayList<AdModel>) request.getServletContext().getAttribute("ads");
if (ads != null) {
    for (AdModel ad : ads) { %>
<div class="ad-title"><%= ad.getTitle()%></div>
<div class="ad-text"><%= ad.getText()%></div>
<div class="ad-username"><%= ad.getUsername()%></div>
<div class="ad-timestamp"><%= ad.getDate()%></div>
<% } %>
<% } %>

</body>
</html>