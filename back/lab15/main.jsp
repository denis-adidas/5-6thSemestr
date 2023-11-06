<%@ page import="org.suai.lab15.AdModel" %>
<%@ page import="java.util.ArrayList" %>

<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" type="text/css" href="style-light.css" id="light-theme">
<%--    <link rel="stylesheet" type="text/css" href="style-dark.css" id="dark-theme">--%>
    <meta charset="UTF-8">
    <title>Fan page about Tyler, The creator</title>
</head>
<body>

<h1>Fan page about Tyler, The creator &#x1F496;</h1>

<% String username = (String)session.getAttribute("username");
    if (username != null) { %>
<h2>Welcome, <%= username %>!</h2>
<a href="${pageContext.request.contextPath}/Logout">Logout</a>
<form action="/lab15/AddAd" method="post">
    <label for="adTitle">Why do you love Tyler? &#128522;</label>
    <input type="text" name="adTitle" id="adTitle" required>
    <br>
    <label for="adText">Tell about it here &#129321;</label>
    <textarea name="adText" id="adText" required></textarea>
    <br>
    <button type="submit">Add ad</button>
</form>
<% } else { %>
<a href="${pageContext.request.contextPath}/Login">Login</a>
<% } %>
<br>

<h2>Ads List</h2>
<% ArrayList<AdModel> ads = (ArrayList<AdModel>) request.getServletContext().getAttribute("ads");
    if (ads != null) {
        for (AdModel ad : ads) { %>
<div class="ad-container">
    <div class="ad-title"><%= ad.getTitle()%></div>
    <div class="ad-text"><%= ad.getText()%></div>
    <div class="ad-username">Posted by: <%= ad.getUsername()%></div>
    <div class="ad-timestamp">Posted on: <%= ad.getDate()%></div>
</div>
<% } %>
<% } %>
<audio controls autoplay>
    <source src="audio.mp3" type="audio/mpeg">

</audio>

</body>
</html>