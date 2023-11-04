package model;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class NotebookSearchServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String searchName = request.getParameter("searchResult");
        request.setAttribute("searchResult", searchName);
        RequestDispatcher dispatcher = request.getRequestDispatcher("/Main.jsp");
        dispatcher.forward(request, response);
    }

}
