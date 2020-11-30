package model.BO;

import model.Bean.Wife;
import model.DAO.CheckLoginDAO;

import java.util.ArrayList;

public class CheckLoginBO {
    CheckLoginDAO checkLoginDAO = new CheckLoginDAO();
    public boolean isValidUser(String username,String password) throws ClassNotFoundException {
        return checkLoginDAO.isExistUser(username,password);
    }
    public ArrayList<Wife> getWifeList() throws ClassNotFoundException {
        return checkLoginDAO.getWifeList();
    }
}
