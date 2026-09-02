import java.sql.*;

public class DatabaseManager {
    private static final String URL = "jdbc:postgresql://localhost:5432/oil_mining_db"; 
    private static final String USER = "postgres";  
    private static final String PASSWORD = "admin";  

    // Connect to the database
    public Connection connect() throws SQLException {
        try {
        Class.forName("org.postgresql.Driver");
    } catch (ClassNotFoundException e) {
        e.printStackTrace();
    }
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }

    // Insert oil well
    public void insertOilWell(String location, double depth, double capacity, String dateDrilled, String status) {
        String insertSQL = "INSERT INTO oil_well (location, depth, capacity, date_drilled, status) VALUES (?, ?, ?, ?, ?)";
        try (
            
            Connection connection = connect();
             PreparedStatement pstmt = connection.prepareStatement(insertSQL)) {
            pstmt.setString(1, location);
            pstmt.setDouble(2, depth);
            pstmt.setDouble(3, capacity);
            java.sql.Date sqlDate = java.sql.Date.valueOf(dateDrilled);  // Ensure the date format is "YYYY-MM-DD"
            pstmt.setDate(4, sqlDate);
            pstmt.setString(5, status);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Read oil wells
    public ResultSet readOilWells() {
        String selectSQL = "SELECT * FROM oil_well";
        try {
            Connection connection = connect();
            PreparedStatement pstmt = connection.prepareStatement(selectSQL);
            return pstmt.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    // Update oil well
    public void updateOilWell(int wellId, String location, double depth, double capacity, String dateDrilled, String status) {
        String updateSQL = "UPDATE oil_well SET location = ?, depth = ?, capacity = ?, date_drilled = ?, status = ? WHERE well_id = ?";
        try (Connection connection = connect();
             PreparedStatement pstmt = connection.prepareStatement(updateSQL)) {
            pstmt.setString(1, location);
            pstmt.setDouble(2, depth);
            pstmt.setDouble(3, capacity);
            java.sql.Date sqlDate = java.sql.Date.valueOf(dateDrilled);  // Ensure the date format is "YYYY-MM-DD"
            pstmt.setDate(4, sqlDate);
            pstmt.setString(5, status);
            pstmt.setInt(6, wellId);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Delete oil well
    public void deleteOilWell(int wellId) {
        String deleteSQL = "DELETE FROM oil_well WHERE well_id = ?";
        try (Connection connection = connect();
             PreparedStatement pstmt = connection.prepareStatement(deleteSQL)) {
            pstmt.setInt(1, wellId);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
