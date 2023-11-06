package org.suai.lab15;

import javax.servlet.*;
import javax.servlet.http.*;
import lombok.SneakyThrows;

import java.io.IOException;

public class LoginServlet extends HttpServlet {

    UserManager userManager = UserManager.loadFromJsonFile("autosave15.json");


    @SneakyThrows
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkAuthenticator(username, password)) {
            HttpSession session = request.getSession(true);
            session.setAttribute("username", username);
            response.sendRedirect("/lab15");
        }
        else {
            response.sendRedirect(request.getContextPath() + "/Login?error");
        }
    }
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("/WEB-INF/login.jsp").forward(request, response);
    }

    public boolean checkAuthenticator(String username, String password) {

        User user = userManager.getUserByName(username);

        if (user != null && user.getPassword().equals(password)) {
            return true;
        }
        else {
            return false;
        }
    }
}
