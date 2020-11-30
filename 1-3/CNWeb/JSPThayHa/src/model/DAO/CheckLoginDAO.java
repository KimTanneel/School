package model.DAO;

import model.Bean.Wife;

import java.sql.*;
import java.util.ArrayList;

public class CheckLoginDAO {
    public boolean isExistUser(String username,String password) throws ClassNotFoundException {
        //Conect DB
        boolean status = false;
        Class.forName("com.mysql.jdbc.Driver");
        try (Connection connection = DriverManager
                .getConnection("jdbc:mysql://localhost:3306/dulieu?useSSL=false", "root", "Leviettrung123");
             // Step 2:Create a statement using connection object
             PreparedStatement preparedStatement = connection.prepareStatement("select * from dulieu.login where username = ? and password = ? ")) {
            preparedStatement.setString(1,username);
            preparedStatement.setString(2,password);

            System.out.println(preparedStatement);
            ResultSet rs = preparedStatement.executeQuery();
            status = rs.next();
//            rs.close();
            connection.close();
        } catch (SQLException e) {
            // process sql exception
            e.printStackTrace();
        }
        return status;

    }

    public ArrayList<Wife> getWifeList() throws ClassNotFoundException {
        ArrayList<Wife> wifeList = new ArrayList<>();
        Class.forName("com.mysql.jdbc.Driver");
        try (
                Connection connection = DriverManager
                .getConnection("jdbc:mysql://localhost:3306/dulieu?useSSL=false", "root", "Leviettrung123");
             // Step 2:Create a statement using connection object
             PreparedStatement preparedStatement = connection.prepareStatement("select * from dulieu.wife ")) {
            System.out.println(preparedStatement);
            ResultSet rs = preparedStatement.executeQuery();
            while (rs.next()) {
                Wife data = new Wife();
                data.setName(rs.getString("name"));
                data.setAddress(rs.getString("address"));
                if(rs.getByte("alive")==1){
                    data.setAlive(true);
                }
                else data.setAlive(false);
                wifeList.add(data);
            }

        } catch (SQLException e) {
            // process sql exception
            e.printStackTrace();
        }
        return wifeList;
    }
}