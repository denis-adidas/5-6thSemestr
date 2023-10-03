package org.example;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class NotebookServlet extends HttpServlet {
    NotebookModel notebook = new NotebookModel();

    public void init(ServletConfig config) {
        notebook.addPerson("Masha");
        notebook.addPerson("Annya");
    }


    public void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        String uri = request.getRequestURI();
        if( uri.equals("/servlet-2/servlet/Testing/add") ) {
            notebook.addPerson(request.getParameter("name"));
        }
        else if( uri.equals("/servlet-2/servlet/Testing/reset") ) {
            notebook.reset();
        }
        PrintWriter out = response.getWriter();
        out.println("<html>\n<body>\n");
        out.println("Last request URI was:" + uri);
        out.println(getMainPage());
        out.println("</body>\n</html>");
    }

    public String getMainPage() {
        StringBuilder sb = new StringBuilder();
        String strNames[] = notebook.getNamesStrings();
        for(int i = 0; i < strNames.length; i++) {
            sb.append("<p>" + strNames[i] + "</p>\n");
        }
        sb.append("<form method=\"GET\" action=\"/servlet-2/servlet/Testing/add\">\n");
        sb.append("Name: <input type=\"text\" name=\"name\">\n"); 
        sb.append("<input type=\"submit\" value=\"add\">\n");
        sb.append("</form>");
        sb.append("<a href=\"/servlet-2/servlet/Testing/reset\">reset</a>");
        return sb.toString();
    }
}
