import java.sql.*;

public class TransactionManager {
    private static final String URL = "jdbc:postgresql://localhost:5432/oil_mining_db"; // Change to your database name
    private static final String USER = "postgres";  // Change to your username
    private static final String PASSWORD = "admin";  // Change to your password

    // Connect to the database
    private Connection connect() throws SQLException {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }

    // Insert a transaction
    public void insertTransaction(int wellId, int buyerId, int sellerId, String transactionDate, double oilQuantity, double pricePerUnit, String transactionType, String paymentMethod) {
        String insertSQL = "INSERT INTO transaction (well_id, buyer_id, seller_id, transaction_date, oil_quantity, price_per_unit, transaction_type, payment_method) " +
                           "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
        try (Connection connection = connect();
             PreparedStatement pstmt = connection.prepareStatement(insertSQL)) {
            pstmt.setInt(1, wellId);
            pstmt.setInt(2, buyerId);
            pstmt.setInt(3, sellerId);
            pstmt.setDate(4, Date.valueOf(transactionDate)); // Convert String to SQL Date
            pstmt.setDouble(5, oilQuantity);
            pstmt.setDouble(6, pricePerUnit);
            pstmt.setString(7, transactionType);
            pstmt.setString(8, paymentMethod);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Update a transaction
    public void updateTransaction(int transactionId, int wellId, int buyerId, int sellerId, String transactionDate, double oilQuantity, double pricePerUnit, String transactionType, String paymentMethod) {
        String updateSQL = "UPDATE transaction SET well_id = ?, buyer_id = ?, seller_id = ?, transaction_date = ?, oil_quantity = ?, price_per_unit = ?, transaction_type = ?, payment_method = ? " +
                           "WHERE transaction_id = ?";
        try (Connection connection = connect();
             PreparedStatement pstmt = connection.prepareStatement(updateSQL)) {
            pstmt.setInt(1, wellId);
            pstmt.setInt(2, buyerId);
            pstmt.setInt(3, sellerId);
            pstmt.setDate(4, Date.valueOf(transactionDate)); // Convert String to SQL Date
            pstmt.setDouble(5, oilQuantity);
            pstmt.setDouble(6, pricePerUnit);
            pstmt.setString(7, transactionType);
            pstmt.setString(8, paymentMethod);
            pstmt.setInt(9, transactionId);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Delete a transaction
    public void deleteTransaction(int transactionId) {
        String deleteSQL = "DELETE FROM transaction WHERE transaction_id = ?";
        try (Connection connection = connect();
             PreparedStatement pstmt = connection.prepareStatement(deleteSQL)) {
            pstmt.setInt(1, transactionId);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Read all transactions
    public ResultSet readTransactions() {
        String selectSQL = "SELECT * FROM transaction";
        try {
            Connection connection = connect();
            PreparedStatement pstmt = connection.prepareStatement(selectSQL);
            return pstmt.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
}
