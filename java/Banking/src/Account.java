import java.util.ArrayList;
import java.util.List;

public class Account {
    private int accountNumber;
    private String accountHolderName;
    private double balance;
    private String email;
    private String phoneNumber;
    private List<Transaction> transactions;

    private boolean isValidEmail(String email) {
        String regex = "^[A-Za-z0-9+_.-]+@(.+)$";
        return email.matches(regex);
    }

    private boolean isValidPhoneNumber(String phoneNumber) {
        String regex = "\\d{10}";
        return phoneNumber.matches(regex);
    }

    public Account(int accountNumber, String accountHolderName, double balance, String email, String phoneNumber) {
        if (!isValidEmail(email)) {
            System.out.println("Invalid email format. Account not created.");
            return;
        }
        if (!isValidPhoneNumber(phoneNumber)) {
            System.out.println("Phone number must be 10 digits. Account not created.");
            return;
        }
        this.accountNumber = accountNumber;
        this.accountHolderName = accountHolderName;
        this.balance = balance;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.transactions = new ArrayList<>();
    }

    public int getAccountNumber() {
        return accountNumber;
    }

    public String getAccountHolderName() {
        return accountHolderName;
    }

    public double getBalance() {
        return balance;
    }

    public String getEmail() {
        return email;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public List<Transaction> getTransactions() {
        return transactions;
    }

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.add(new Transaction(TransactionType.DEPOSIT, amount));
            System.out.println("Deposit successful. New balance: Rs. " + balance);
        } else {
            System.out.println("Invalid deposit amount.");
        }
    }

    public void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.add(new Transaction(TransactionType.WITHDRAWAL, amount));
            System.out.println("Withdrawal successful. New balance: Rs. " + balance);
        } else {
            System.out.println("Invalid withdrawal amount or insufficient balance.");
        }
    }

    public void displayAccountDetails() {
        System.out.println("Account Number: " + accountNumber);
        System.out.println("Account Holder Name: " + accountHolderName);
        System.out.println("Balance: Rs. " + balance);
        System.out.println("Email: " + email);
        System.out.println("Phone Number: " + phoneNumber);
    }

    public void displayTransactionHistory() {
        System.out.println("Transaction History for Account " + accountNumber + ":");
        if (transactions.isEmpty()) {
            System.out.println("No transactions found.");
        } else {
            for (Transaction transaction : transactions) {
                System.out.println(transaction);
            }
        }
    }

    public void updateContactDetails(String email, String phoneNumber) {
        if (!isValidEmail(email)) {
            System.out.println("Invalid email format. Contact details not updated.");
            return;
        }
        if (!isValidPhoneNumber(phoneNumber)) {
            System.out.println("Phone number must be 10 digits. Contact details not updated.");
            return;
        }
        this.email = email;
        this.phoneNumber = phoneNumber;
        System.out.println("Contact details updated successfully.");
    }
}
