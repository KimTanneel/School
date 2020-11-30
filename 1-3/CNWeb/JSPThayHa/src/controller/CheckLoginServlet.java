package controller;

import model.BO.CheckLoginBO;
import model.Bean.Wife;

import javax.servlet.RequestDispatcher;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;

@WebServlet(name = "CheckLoginServlet", urlPatterns = "/login")
public class CheckLoginServlet extends javax.servlet.http.HttpServlet {
    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        String destination =null;
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        CheckLoginBO checkLoginBO = new CheckLoginBO();
        ArrayList<Wife> wifeArray = new ArrayList<>();
        try {
            if(checkLoginBO.isValidUser(username,password)){

                HttpSession session = request.getSession();
                session.setAttribute("user", username);
                destination="/wife";
                String site = new String("http://localhost:8081/wife");

                response.setStatus(response.SC_MOVED_TEMPORARILY);
                response.setHeader("Location", site);

            }
            else destination="/WEB-INF/Login.jsp";
            System.out.println(destination);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        RequestDispatcher requestDispatcher = getServletContext().getRequestDispatcher(destination);
        requestDispatcher.forward(request, response);

    }

    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        String destination = "/WEB-INF/Login.jsp";
        RequestDispatcher requestDispatcher = getServletContext().getRequestDispatcher(destination);
        requestDispatcher.forward(request, response);
    }
}
