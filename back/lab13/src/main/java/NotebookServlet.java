import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class NotebookServlet extends HttpServlet {
    NotebookModel notebook = new NotebookModel();

    public void init(ServletConfig config) {
        NotebookModel.loadFromJsonFile("autosave.json");
    }


    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String uri = request.getRequestURI();
        boolean secondPage = false;


        switch (uri) {
            case "/lab13/Notebook/getName" -> {
                notebook.addPerson(request.getParameter("name"));
                secondPage = true;
            }
            case "/lab13/Notebook/number" -> {
                notebook.addPersonNumber(request.getParameter("name"), request.getParameter("number"));
                secondPage = false;
                notebook.saveToJsonFile("autosave.json");
            }
            case "/lab13/Notebook/reset" -> {
                notebook.reset();
                secondPage = false;
                notebook.saveToJsonFile("autosave.json");
            }
        }
        PrintWriter out = response.getWriter();
        out.println("<html>\n<body>\n");
        if (secondPage == true)
            out.println(getOnePerson(request.getParameter("name")));
        else
            out.println(getMainPage());
        out.println("Last request URI was:" + uri);
        out.println("</body>\n</html>");
    }

    public String getMainPage() {
        StringBuilder sb = new StringBuilder();
        for (NotebookModel.Person x : notebook.getPersons()) {
            sb.append("<p>").append(x.toString()).append("</p>");
        }
        sb.append("<form method=\"GET\" action=\"/lab13/Notebook/number\">\n");
        sb.append("Name: <input type=\"text\" name=\"name\">\n");
        sb.append("Number: <input type=\"text\" name=\"number\">\n");
        sb.append("<input type=\"submit\" value=\"add\">\n");
        sb.append("</form>");

        sb.append("<form method=\"GET\" action=\"/lab13/Notebook/getName\">\n");
        sb.append("Name: <input type=\"text\" name=\"name\">\n");
        sb.append("<input type=\"submit\" value=\"get\">\n");
        sb.append("</form>");



        sb.append("<a href=\"/lab13/Notebook/reset\">reset</a>");
        return sb.toString();
    }
    public String getOnePerson(String name) {
        StringBuilder sb = new StringBuilder();
        for (NotebookModel.Person x : notebook.getPersons()) {
            if (x.getName().equals(name))
                sb.append("<p>").append(x.toString()).append("</p>");
        }
        sb.append("<form method=\"GET\" action=\"/lab13/Notebook/number\">\n");
        sb.append("Name: <input type=\"text\" name=\"name\">\n");
        sb.append("Number: <input type=\"text\" name=\"number\">\n");
        sb.append("<input type=\"submit\" value=\"add\">\n");
        sb.append("</form>");

        sb.append("<form method=\"GET\" action=\"/lab13/Notebook/getName\">\n");
        sb.append("Name: <input type=\"text\" name=\"name\">\n");
        sb.append("<input type=\"submit\" value=\"get\">\n");
        sb.append("</form>");

        sb.append("<a href=\"/lab13/Notebook/reset\">reset</a>");
        return sb.toString();
    }
    @Override
    public void destroy() {
        notebook.saveToJsonFile("autosave.json");
    }
}
