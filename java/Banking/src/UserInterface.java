import java.io.*;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class UserInterface {
    private List<Account> accounts = new ArrayList<>();
    private Scanner scanner = new Scanner(System.in);
    private int nextAccountNumber = 1;
    private static final String DATA_FILE = "accounts.csv";

    public static void main(String[] args) {
        UserInterface ui = new UserInterface();
        ui.mainMenu();
    }

    public void mainMenu() {
        loadAccounts();
        while (true) {
            System.out.println("\nWelcome to the Banking Application!");
            System.out.println("1. Create a new account");
            System.out.println("2. Deposit money");
            System.out.println("3. Withdraw money");
            System.out.println("4. View account details");
            System.out.println("5. View transaction history");
            System.out.println("6. View all accounts");
            System.out.println("7. Update contact details");
            System.out.println("8. Exit");
            System.out.print("Enter your choice: ");
            try {
                int choice = scanner.nextInt();
                scanner.nextLine();

                switch (choice) {
                    case 1:
                        createAccount();
                        break;
                    case 2:
                        performDeposit();
                        break;
                    case 3:
                        performWithdrawal();
                        break;
                    case 4:
                        showAccountDetails();
                        break;
                    case 5:
                        showTransactionHistory();
                        break;
                    case 6:
                        viewAllAccounts();
                        break;
                    case 7:
                        updateContact();
                        break;
                    case 8:
                        saveAccounts();
                        System.out.println("Exiting application.");
                        return;
                    default:
                        System.out.println("Invalid choice. Please try again.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a number.");
                scanner.nextLine();
            }
        }
    }

    public void createAccount() {
        System.out.print("Enter account holder name: ");
        String name = scanner.nextLine();
        double balance = 0;
        while (true) {
            try {
                System.out.print("Enter initial deposit amount (in INR): ");
                balance = scanner.nextDouble();
                scanner.nextLine();
                if (balance >= 0) {
                    break;
                }
                System.out.println("Initial deposit cannot be negative.");
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a number.");
                scanner.nextLine();
            }
        }
        System.out.print("Enter email address: ");
        String email = scanner.nextLine();
        System.out.print("Enter phone number: ");
        String phone = scanner.nextLine();

        Account newAccount = new Account(nextAccountNumber, name, balance, email, phone);
        if (newAccount.getAccountNumber() != 0) {
            accounts.add(newAccount);
            System.out.println("Account created successfully with Account Number: " + nextAccountNumber);
            nextAccountNumber++;
        }
    }

    public void performDeposit() {
        try {
            System.out.print("Enter account number: ");
            int accNum = scanner.nextInt();
            Account acc = findAccount(accNum);
            if (acc != null) {
                System.out.print("Enter amount to deposit (in INR): ");
                double amount = scanner.nextDouble();
                acc.deposit(amount);
            } else {
                System.out.println("Account not found.");
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter a number.");
            scanner.nextLine();
        }
    }

    public void performWithdrawal() {
        try {
            System.out.print("Enter account number: ");
            int accNum = scanner.nextInt();
            Account acc = findAccount(accNum);
            if (acc != null) {
                System.out.print("Enter amount to withdraw (in INR): ");
                double amount = scanner.nextDouble();
                acc.withdraw(amount);
            } else {
                System.out.println("Account not found.");
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter a number.");
            scanner.nextLine();
        }
    }

    public void showAccountDetails() {
        try {
            System.out.print("Enter account number: ");
            int accNum = scanner.nextInt();
            Account acc = findAccount(accNum);
            if (acc != null) {
                acc.displayAccountDetails();
            } else {
                System.out.println("Account not found.");
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter a number.");
            scanner.nextLine();
        }
    }

    public void showTransactionHistory() {
        try {
            System.out.print("Enter account number: ");
            int accNum = scanner.nextInt();
            Account acc = findAccount(accNum);
            if (acc != null) {
                acc.displayTransactionHistory();
            } else {
                System.out.println("Account not found.");
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter a number.");
            scanner.nextLine();
        }
    }

    public void viewAllAccounts() {
        System.out.println("\nAll Accounts:");
        if (accounts.isEmpty()) {
            System.out.println("No accounts found.");
        } else {
            for (Account acc : accounts) {
                acc.displayAccountDetails();
                System.out.println();
            }
        }
    }

    public void updateContact() {
        try {
            System.out.print("Enter account number: ");
            int accNum = scanner.nextInt();
            scanner.nextLine();
            Account acc = findAccount(accNum);
            if (acc != null) {
                System.out.print("Enter new email address: ");
                String email = scanner.nextLine();
                System.out.print("Enter new phone number: ");
                String phone = scanner.nextLine();
                acc.updateContactDetails(email, phone);
            } else {
                System.out.println("Account not found.");
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter a number.");
            scanner.nextLine();
        }
    }

    private Account findAccount(int accountNumber) {
        for (Account account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return null;
    }

    private void saveAccounts() {
        try (PrintWriter writer = new PrintWriter(new FileWriter(DATA_FILE))) {
            for (Account account : accounts) {
                writer.println(account.getAccountNumber() + "," + account.getAccountHolderName() + "," +
                        account.getBalance() + "," + account.getEmail() + "," + account.getPhoneNumber());
            }
        } catch (IOException e) {
            System.out.println("Error saving accounts: " + e.getMessage());
        }
    }

    private void loadAccounts() {
        File file = new File(DATA_FILE);
        if (!file.exists()) {
            return;
        }
        try (BufferedReader reader = new BufferedReader(new FileReader(DATA_FILE))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] data = line.split(",");
                if (data.length == 5) {
                    int accountNumber = Integer.parseInt(data[0]);
                    String accountHolderName = data[1];
                    double balance = Double.parseDouble(data[2]);
                    String email = data[3];
                    String phoneNumber = data[4];
                    accounts.add(new Account(accountNumber, accountHolderName, balance, email, phoneNumber));
                    if (accountNumber >= nextAccountNumber) {
                        nextAccountNumber = accountNumber + 1;
                    }
                }
            }
        } catch (IOException | NumberFormatException e) {
            System.out.println("Error loading accounts: " + e.getMessage());
        }
    }
}