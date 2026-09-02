import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

public class TransactionGUI extends JFrame {
    private JTextField wellIdField, buyerIdField, sellerIdField, transactionDateField, oilQuantityField, pricePerUnitField, transactionTypeField, paymentMethodField;
    private JButton addButton, updateButton, deleteButton, loadButton;
    private JTable transactionTable;
    private DefaultTableModel tableModel;
    private TransactionManager transactionManager;

    public TransactionGUI() {
        transactionManager = new TransactionManager();
        setTitle("Transaction Management");
        setLayout(new BorderLayout());

        // Input panel
        JPanel inputPanel = new JPanel(new GridLayout(9, 2));
        inputPanel.add(new JLabel("Well ID:"));
        wellIdField = new JTextField();
        inputPanel.add(wellIdField);

        inputPanel.add(new JLabel("Buyer ID:"));
        buyerIdField = new JTextField();
        inputPanel.add(buyerIdField);

        inputPanel.add(new JLabel("Seller ID:"));
        sellerIdField = new JTextField();
        inputPanel.add(sellerIdField);

        inputPanel.add(new JLabel("Transaction Date (YYYY-MM-DD):"));
        transactionDateField = new JTextField();
        inputPanel.add(transactionDateField);

        inputPanel.add(new JLabel("Oil Quantity:"));
        oilQuantityField = new JTextField();
        inputPanel.add(oilQuantityField);

        inputPanel.add(new JLabel("Price Per Unit:"));
        pricePerUnitField = new JTextField();
        inputPanel.add(pricePerUnitField);

        inputPanel.add(new JLabel("Transaction Type:"));
        transactionTypeField = new JTextField();
        inputPanel.add(transactionTypeField);

        inputPanel.add(new JLabel("Payment Method:"));
        paymentMethodField = new JTextField();
        inputPanel.add(paymentMethodField);

        // Button panel
        JPanel buttonPanel = new JPanel();
        addButton = new JButton("Add");
        updateButton = new JButton("Update");
        deleteButton = new JButton("Delete");
        loadButton = new JButton("Load");
        buttonPanel.add(addButton);
        buttonPanel.add(updateButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(loadButton);

        // Table
        tableModel = new DefaultTableModel(new String[]{"Transaction ID", "Well ID", "Buyer ID", "Seller ID", "Transaction Date", "Oil Quantity", "Price Per Unit", "Transaction Type", "Payment Method"}, 0);
        transactionTable = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(transactionTable);

        // Add components to the frame
        add(inputPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);

        // Action listeners
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int wellId = Integer.parseInt(wellIdField.getText());
                int buyerId = Integer.parseInt(buyerIdField.getText());
                int sellerId = Integer.parseInt(sellerIdField.getText());
                String transactionDate = transactionDateField.getText();
                double oilQuantity = Double.parseDouble(oilQuantityField.getText());
                double pricePerUnit = Double.parseDouble(pricePerUnitField.getText());
                String transactionType = transactionTypeField.getText();
                String paymentMethod = paymentMethodField.getText();
                transactionManager.insertTransaction(wellId, buyerId, sellerId, transactionDate, oilQuantity, pricePerUnit, transactionType, paymentMethod);
                loadTransactions();
            }
        });

        updateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int transactionId = Integer.parseInt(JOptionPane.showInputDialog("Enter Transaction ID to Update:"));
                int wellId = Integer.parseInt(wellIdField.getText());
                int buyerId = Integer.parseInt(buyerIdField.getText());
                int sellerId = Integer.parseInt(sellerIdField.getText());
                String transactionDate = transactionDateField.getText();
                double oilQuantity = Double.parseDouble(oilQuantityField.getText());
                double pricePerUnit = Double.parseDouble(pricePerUnitField.getText());
                String transactionType = transactionTypeField.getText();
                String paymentMethod = paymentMethodField.getText();
                transactionManager.updateTransaction(transactionId, wellId, buyerId, sellerId, transactionDate, oilQuantity, pricePerUnit, transactionType, paymentMethod);
                loadTransactions();
            }
        });

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int transactionId = Integer.parseInt(JOptionPane.showInputDialog("Enter Transaction ID to Delete:"));
                transactionManager.deleteTransaction(transactionId);
                loadTransactions();
            }
        });

        loadButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                loadTransactions();
            }
        });

        setSize(900, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    // Load transactions into the table
    private void loadTransactions() {
        try {
            ResultSet resultSet = transactionManager.readTransactions();
            tableModel.setRowCount(0); // Clear existing data
            while (resultSet != null && resultSet.next()) {
                int transactionId = resultSet.getInt("transaction_id");
                int wellId = resultSet.getInt("well_id");
                int buyerId = resultSet.getInt("buyer_id");
                int sellerId = resultSet.getInt("seller_id");
                String transactionDate = resultSet.getString("transaction_date");
                double oilQuantity = resultSet.getDouble("oil_quantity");
                double pricePerUnit = resultSet.getDouble("price_per_unit");
                String transactionType = resultSet.getString("transaction_type");
                String paymentMethod = resultSet.getString("payment_method");
                tableModel.addRow(new Object[]{transactionId, wellId, buyerId, sellerId, transactionDate, oilQuantity, pricePerUnit, transactionType, paymentMethod});
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new TransactionGUI();
    }
}
