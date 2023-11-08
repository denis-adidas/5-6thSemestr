package org.suai.lab15;

import javax.servlet.http.*;
import lombok.SneakyThrows;

import java.util.ArrayList;


public class DeleteAllAdsServlet extends HttpServlet {
    @SneakyThrows
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        ArrayList<AdModel> ads = (ArrayList<AdModel>) getServletContext().getAttribute("ads");

        if (ads != null && !ads.isEmpty()) {
            ads.clear();

            getServletContext().setAttribute("ads", ads);
        }

        response.sendRedirect(request.getContextPath());
    }
}