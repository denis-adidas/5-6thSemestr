package org.suai.lab15;

import java.io.*;
import java.util.ArrayList;

import javax.servlet.*;
import javax.servlet.http.*;
import lombok.SneakyThrows;

public class AddAdServlet extends HttpServlet {
    private String message;

    @Override
    public void init() {
        ArrayList<AdModel> allAds = new ArrayList<>();

        getServletContext().setAttribute("ads", allAds);
    }

    @SneakyThrows
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession(false);

        if (session != null) {
            String username = (String)session.getAttribute("username");
            String adTitle = request.getParameter("adTitle");
            String adText = request.getParameter("adText");

            if (adTitle != null && adText != null) {
                AdModel newAd = new AdModel(adTitle, adText, username);
                @SuppressWarnings("unchecked")
                ArrayList<AdModel> allAds = (ArrayList<AdModel>) getServletContext().getAttribute("ads");
                allAds.add(newAd);
            }
        }
        response.sendRedirect(request.getContextPath());
    }
    @Override
    public void destroy() {
    }
}