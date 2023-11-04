package model;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class NotebookServlet extends HttpServlet {
    NotebookModel notebook = new NotebookModel();

    @Override
    public void init(ServletConfig config) {
        NotebookModel.loadFromJsonFile("autosave.json");
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uri = request.getRequestURI();

        switch (uri) {
            case "/lab13/NoteBook/number" -> {
                notebook.addPersonNumber(request.getParameter("name"), request.getParameter("number"));
                notebook.saveToJsonFile("autosave.json");
            }
            case "/lab13/NoteBook/reset" -> {
                notebook.reset();
                notebook.saveToJsonFile("autosave.json");
            }
        }
        request.setAttribute("notes", notebook.getPersons());
        request.getRequestDispatcher("/Main.jsp").forward(request, response);
    }
    @Override
    public void destroy() {
        notebook.saveToJsonFile("autosave.json");
    }
}
