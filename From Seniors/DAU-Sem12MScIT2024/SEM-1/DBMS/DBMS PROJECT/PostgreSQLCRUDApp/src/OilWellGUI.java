import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

public class OilWellGUI extends JFrame {
    private JTextField idField, locationField, depthField, capacityField, dateDrilledField, statusField;
    private JButton addButton, updateButton, deleteButton, loadButton, viewTransactionsButton;
    private JTable oilWellTable;
    private DefaultTableModel tableModel;
    private DatabaseManager dbManager;
    private TransactionManager transactionManager;

    public OilWellGUI() {
        dbManager = new DatabaseManager();
        transactionManager = new TransactionManager();
        setTitle("Oil Well Management and Usage");
        setLayout(new BorderLayout());

        // Input panel
        JPanel inputPanel = new JPanel(new GridLayout(6, 2));
        inputPanel.add(new JLabel("Well ID:"));
        idField = new JTextField();
        inputPanel.add(idField);

        inputPanel.add(new JLabel("Location:"));
        locationField = new JTextField();
        inputPanel.add(locationField);

        inputPanel.add(new JLabel("Depth:"));
        depthField = new JTextField();
        inputPanel.add(depthField);

        inputPanel.add(new JLabel("Capacity:"));
        capacityField = new JTextField();
        inputPanel.add(capacityField);

        inputPanel.add(new JLabel("Date Drilled:"));
        dateDrilledField = new JTextField();
        inputPanel.add(dateDrilledField);

        inputPanel.add(new JLabel("Status:"));
        statusField = new JTextField();
        inputPanel.add(statusField);

        // Button panel
        JPanel buttonPanel = new JPanel();
        addButton = new JButton("Add");
        updateButton = new JButton("Update");
        deleteButton = new JButton("Delete");
        loadButton = new JButton("Load");
        viewTransactionsButton = new JButton("View Transactions");
        buttonPanel.add(addButton);
        buttonPanel.add(updateButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(loadButton);
        buttonPanel.add(viewTransactionsButton);

        // Table
        tableModel = new DefaultTableModel(new String[]{"Well ID", "Location", "Depth", "Capacity", "Date Drilled", "Status"}, 0);
        oilWellTable = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(oilWellTable);

        // Add components to the frame
        add(inputPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);

        // Action listeners
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String location = locationField.getText();
                double depth = Double.parseDouble(depthField.getText());
                double capacity = Double.parseDouble(capacityField.getText());
                String dateDrilled = dateDrilledField.getText();
                String status = statusField.getText();
                dbManager.insertOilWell(location, depth, capacity, dateDrilled, status);
                loadOilWells();
            }
        });

        updateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int id = Integer.parseInt(idField.getText());
                String location = locationField.getText();
                double depth = Double.parseDouble(depthField.getText());
                double capacity = Double.parseDouble(capacityField.getText());
                String dateDrilled = dateDrilledField.getText();
                String status = statusField.getText();
                dbManager.updateOilWell(id, location, depth, capacity, dateDrilled, status);
                loadOilWells();
            }
        });

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int id = Integer.parseInt(idField.getText());
                dbManager.deleteOilWell(id);
                loadOilWells();
            }
        });

        loadButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                loadOilWells();
            }
        });

        viewTransactionsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // SQL query and the English explanation
                String sqlQuery = "SELECT ow.location AS well_location, t.transaction_id, t.transaction_date, t.oil_quantity, t.price_per_unit, " +
                        "t.transaction_type, t.payment_method, t.delivery_date, t.buyer_id, t.seller_id " +
                        "FROM oil_well ow JOIN transaction t ON ow.well_id = t.well_id ORDER BY t.transaction_date DESC";
                
                String englishQuery = "The SQL query retrieves details about transactions for each oil well. " +
                        "It includes the well's location, transaction ID, transaction date, oil quantity, price per unit, " +
                        "transaction type, payment method, delivery date, buyer ID, and seller ID.";

                // Show the SQL query and explanation in a message box
                JOptionPane.showMessageDialog(OilWellGUI.this, englishQuery + "\n\nSQL Query:\n" + sqlQuery, "SQL Query for Transactions", JOptionPane.INFORMATION_MESSAGE);

                // Display the transactions in a maximized dialog
                loadOilWellTransactions(sqlQuery);
            }
        });

        // Set the frame size to maximized state
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    // Load oil wells into the table
    private void loadOilWells() {
        try {
            ResultSet resultSet = dbManager.readOilWells();
            tableModel.setRowCount(0); // Clear existing data
            while (resultSet != null && resultSet.next()) {
                int id = resultSet.getInt("well_id");
                String location = resultSet.getString("location");
                double depth = resultSet.getDouble("depth");
                double capacity = resultSet.getDouble("capacity");
                String dateDrilled = resultSet.getString("date_drilled");
                String status = resultSet.getString("status");
                tableModel.addRow(new Object[]{id, location, depth, capacity, dateDrilled, status});
            }
            adjustTableColumns(oilWellTable);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Adjust column widths based on the content
    private void adjustTableColumns(JTable table) {
        for (int columnIndex = 0; columnIndex < table.getColumnCount(); columnIndex++) {
            TableColumn column = table.getColumnModel().getColumn(columnIndex);
            int maxWidth = 0;
            for (int rowIndex = 0; rowIndex < table.getRowCount(); rowIndex++) {
                int cellWidth = table.getCellRenderer(rowIndex, columnIndex).getTableCellRendererComponent(
                        table, table.getValueAt(rowIndex, columnIndex), false, false, rowIndex, columnIndex).getPreferredSize().width;
                maxWidth = Math.max(maxWidth, cellWidth);
            }
            column.setPreferredWidth(maxWidth + 10);  // Add extra padding for readability
        }
    }

    // Load oil well transactions and show them in a maximized dialog
    // Load oil well transactions and show them in a maximized dialog
private void loadOilWellTransactions(String sqlQuery) {
    try {
        Connection connection = dbManager.connect();
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        ResultSet resultSet = pstmt.executeQuery();

        // Create a new table for the transaction data
        DefaultTableModel transactionTableModel = new DefaultTableModel(new String[]{
                "Well Location", "Transaction ID", "Transaction Date", "Oil Quantity", "Price per Unit", "Transaction Type",
                "Payment Method", "Delivery Date", "Buyer ID", "Seller ID"
        }, 0);

        // Adding data to the transaction table model
        while (resultSet != null && resultSet.next()) {
            String location = resultSet.getString("well_location");
            int transactionId = resultSet.getInt("transaction_id");
            String transactionDate = resultSet.getString("transaction_date");
            double oilQuantity = resultSet.getDouble("oil_quantity");
            double pricePerUnit = resultSet.getDouble("price_per_unit");
            String transactionType = resultSet.getString("transaction_type");
            String paymentMethod = resultSet.getString("payment_method");
            String deliveryDate = resultSet.getString("delivery_date");
            int buyerId = resultSet.getInt("buyer_id");
            int sellerId = resultSet.getInt("seller_id");

            transactionTableModel.addRow(new Object[]{location, transactionId, transactionDate, oilQuantity, pricePerUnit,
                    transactionType, paymentMethod, deliveryDate, buyerId, sellerId});
        }

        // Create and show the transaction dialog
        JDialog transactionDialog = new JDialog(this, "Oil Well Transactions", true);
        transactionDialog.setLayout(new BorderLayout());
        JTable transactionTable = new JTable(transactionTableModel);
        JScrollPane scrollPane = new JScrollPane(transactionTable);
        transactionDialog.add(scrollPane, BorderLayout.CENTER);

        // Maximizing the dialog by setting its size to the screen dimensions
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        transactionDialog.setSize(screenSize); // Set the dialog size to the full screen size
        transactionDialog.setLocationRelativeTo(this); // Center the dialog relative to the parent window
        transactionDialog.setVisible(true);

    } catch (SQLException e) {
        e.printStackTrace();
    }
}


    public static void main(String[] args) {
        new OilWellGUI();
    }
}
