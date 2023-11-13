import lombok.SneakyThrows;

import javax.servlet.RequestDispatcher;
import javax.servlet.http.*;

public class ToggleListServlet extends HttpServlet {
    private static ToggleList list;

    @Override
    public void init() {
        list = new ToggleList("autosave.json");
    }
    @Override
    @SneakyThrows
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/main.jsp");
        request.setAttribute("toggleList", list.getLists());
        dispatcher.forward(request, response);
    }
}
