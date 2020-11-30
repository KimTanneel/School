package controller;

import model.BO.WifeBO;
import model.Bean.Wife;


import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.*;
import java.util.List;

@WebServlet(name = "WifeControl",urlPatterns = "/wife")

public class WifeControl extends HttpServlet {
    private model.BO.WifeBO WifeBO;
    public void init(){
        WifeBO = new WifeBO();
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action= request.getParameter("action");
        if(action==null){
            action="";
        }
        try {
            switch (action) {
                case "create":
                    insertUser(request, response);
                    break;
                case "edit":
                    updateUser(request, response);
                    break;
                default:

            }
        } catch (SQLException ex) {
            throw new ServletException(ex);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action= request.getParameter("action");
        if(action==null){
            action="";
        }
        try{
            switch (action) {
                case "create":
                    System.out.println("Create Action Finished");
                    showNewForm(request, response);
                    break;
                case "edit":
                    showEditForm(request, response);
                    break;
                case "delete":
                    deleteWife(request, response);
                    break;
                default:
                    listWife(request, response);
                    break;
            }
        }
        catch (SQLException ex){
            ex.printStackTrace();
        }
    }

    private void showNewForm(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getRequestDispatcher("WEB-INF/create.jsp");
        dispatcher.forward(request, response);
    }
    private void showEditForm(HttpServletRequest request, HttpServletResponse response)
            throws SQLException, ServletException, IOException {
        String name = (request.getParameter("name"));
        Wife existingUser = WifeBO.selectWife(name);
        RequestDispatcher dispatcher = request.getRequestDispatcher("WEB-INF/edit.jsp");
        request.setAttribute("wife", existingUser);
        dispatcher.forward(request, response);

    }

    private void insertUser(HttpServletRequest request, HttpServletResponse response)
            throws SQLException, IOException, ServletException {
        String name = request.getParameter("name");
        String address = request.getParameter("address");
        Boolean alive = null;
        if(request.getParameter("alive").equals("true")){
             alive = true;
        }
        else {
            alive = false;
        }
        Wife newWife = new Wife(name, address,alive );
        WifeBO.insertWife(newWife);
        request.setAttribute("listWife", WifeBO.selectAllWifes());
        RequestDispatcher dispatcher = request.getRequestDispatcher("WEB-INF/list.jsp");
        dispatcher.forward(request, response);
    }
    private void listWife(HttpServletRequest request, HttpServletResponse response)
            throws SQLException, IOException, ServletException {
        List<Wife> listWife = WifeBO.selectAllWifes();
        request.setAttribute("listWife", listWife);
        RequestDispatcher dispatcher = request.getRequestDispatcher("WEB-INF/list.jsp");
        dispatcher.forward(request, response);
    }
    private void updateUser(HttpServletRequest request, HttpServletResponse response)
            throws SQLException, IOException, ServletException {
        String name = request.getParameter("name");
        String address = request.getParameter("address");
        Boolean alive = true;
        System.out.println(request.getParameter("alive"));
        if(request.getParameter("alive").equals("false")){
            alive = false;
        }
        Wife wife = new Wife( name, address,alive);
        WifeBO.updateWife(wife);
        request.setAttribute("listWife", WifeBO.selectAllWifes());
        RequestDispatcher dispatcher = request.getRequestDispatcher("WEB-INF/list.jsp");
        dispatcher.forward(request, response);
    }
    public void deleteWife(HttpServletRequest request, HttpServletResponse response) throws SQLException, ServletException, IOException {
        String name = request.getParameter("name");
        WifeBO.deleteWife(name);
        request.setAttribute("listWife", WifeBO.selectAllWifes());
        RequestDispatcher dispatcher = request.getRequestDispatcher("WEB-INF/list.jsp");
        dispatcher.forward(request, response);
    }
}
