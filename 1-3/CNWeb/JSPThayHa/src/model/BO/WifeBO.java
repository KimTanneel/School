package model.BO;

import model.Bean.Wife;
import model.DAO.WifeDAO;

import java.sql.SQLException;
import java.util.List;

public class WifeBO {
    private WifeDAO WifeDAO;
    public WifeBO(){
        WifeDAO = new WifeDAO();
    }
    public void insertWife(Wife wife) throws SQLException {
        WifeDAO.insertWife(wife);
    }
    public Wife selectWife(String name){
        return WifeDAO.selectWife(name);
    }
    public List<Wife> selectAllWifes(){
        return WifeDAO.selectAllWifes();
    }
    public boolean deleteWife(String name) throws SQLException {
        return WifeDAO.deleteWife(name);
    }
    public boolean updateWife(Wife wife) throws SQLException {
        return WifeDAO.updateWife(wife);
    }
}
