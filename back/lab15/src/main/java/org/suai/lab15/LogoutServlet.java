package org.suai.lab15;

import javax.servlet.*;
import javax.servlet.http.*;
import lombok.SneakyThrows;


public class LogoutServlet extends HttpServlet {
    @SneakyThrows
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession(false);
        session.invalidate();
        response.sendRedirect(request.getContextPath());
    }
}
