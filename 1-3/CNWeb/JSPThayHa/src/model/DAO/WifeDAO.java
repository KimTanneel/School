package model.DAO;

import model.Bean.Wife;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class WifeDAO {
    private String jdbcURL = "jdbc:mysql://localhost:3306/dulieu?useSSL=false";
    private String jdbcUsername = "root";
    private String jdbcPassword = "Leviettrung123";

    private static final String INSERT_USERS_SQL = "INSERT INTO dulieu.wife" + "  (name, address, alive) VALUES " +
            " (?, ?, ?);";

    private static final String SELECT_USER_BY_ID = "select name,address,alive from dulieu.wife where name =?";
    private static final String SELECT_ALL_USERS = "select * from dulieu.wife";
    private static final String DELETE_USERS_SQL = "delete from dulieu.wife where name = ?;";
    private static final String UPDATE_USERS_SQL =  "update dulieu.wife set address= ?, alive =? where name = ?;";

    protected Connection getConnection() {
        Connection connection = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            connection = DriverManager.getConnection(jdbcURL, jdbcUsername, jdbcPassword);
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return connection;
    }

    public void insertWife(Wife wife) throws SQLException {
        System.out.println(INSERT_USERS_SQL);
        // try-with-resource statement will auto close the connection.
        try (Connection connection = getConnection(); PreparedStatement preparedStatement = connection.prepareStatement(INSERT_USERS_SQL)) {
            preparedStatement.setString(1, wife.getName());
            preparedStatement.setString(2, wife.getAddress());
            if(wife.isAlive()) {
                preparedStatement.setString(3, "1");
            }
            else {
                preparedStatement.setString(3, "0");
            }
            System.out.println(preparedStatement);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Wife selectWife(String name) {
        Wife wife = null;
        // Step 1: Establishing a Connection

        try (Connection connection = getConnection();
             // Step 2:Create a statement using connection object
             PreparedStatement preparedStatement = connection.prepareStatement(SELECT_USER_BY_ID);) {
            preparedStatement.setString(1, name);
            System.out.println(preparedStatement);
            // Step 3: Execute the query or update query
            ResultSet rs = preparedStatement.executeQuery();

            // Step 4: Process the ResultSet object.
            while (rs.next()) {
//                String name = rs.getString("name");
                String address = rs.getString("address");
                Boolean alive =null;
                if (rs.getByte("alive") == 1) {
                    alive = true;
                }
                else{
                    alive = false;
                }

                    wife = new Wife(name, address, alive);

            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return wife;
    }

    public List<Wife> selectAllWifes() {

        // using try-with-resources to avoid closing resources (boiler plate code)
        List<Wife> wifeList = new ArrayList<>();
        // Step 1: Establishing a Connection
        try (Connection connection = getConnection();

             // Step 2:Create a statement using connection object
             PreparedStatement preparedStatement = connection.prepareStatement(SELECT_ALL_USERS);) {
            System.out.println(preparedStatement);
            // Step 3: Execute the query or update query
            ResultSet rs = preparedStatement.executeQuery();

            // Step 4: Process the ResultSet object.
            while (rs.next()) {
                Boolean alive=null;

                String name = rs.getString("name");
                String address = rs.getString("address");
                if(rs.getByte("alive")==1){
                    alive = true;
                }
                else{
                    alive = false;
                };
                wifeList.add(new Wife(name, address, alive));

            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return wifeList;
    }
    public boolean deleteWife(String name) throws SQLException {
        boolean rowDeleted;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(DELETE_USERS_SQL);) {
            statement.setString(1, name);
            rowDeleted = statement.executeUpdate() > 0;
        }
        return rowDeleted;
    }
    public boolean updateWife(Wife wife) throws SQLException {
        boolean rowUpdated;
        try (Connection connection = getConnection(); PreparedStatement statement = connection.prepareStatement(UPDATE_USERS_SQL);) {
            statement.setString(1, wife.getAddress());
            statement.setString(3, wife.getName());
            if (wife.isAlive()) {
                statement.setString(2,"1");
            }
            else{
                statement.setString(2,"0");
            }
            System.out.println(statement.toString());
            rowUpdated = statement.executeUpdate() > 0;
        }

        return rowUpdated;
    }

}
