public class Bank {

    static class InvalidAmountException extends Exception {
        InvalidAmountException(String msg) {
            super(msg);
        }
    }

    static class InsufficientFundsException extends Exception {
        InsufficientFundsException(String msg) {
            super(msg);
        }
    }

    class Account {
        private final int accountNo;
        private double balance;

        Account(int accountNo, double openingBalance) throws InvalidAmountException {
            if (openingBalance < 0) {
                throw new InvalidAmountException("Opening Balance cannot be negative");
            }
            this.accountNo = accountNo;
            this.balance = openingBalance;
        }

        public double getBalance() {
            return balance;
        }

        public void deposit(double amount) throws InvalidAmountException {
            if (amount <= 0) {
                throw new InvalidAmountException("Deposit amount should be more than 0");
            }
            balance += amount;

        }

        public void withdraw(double amount) throws InvalidAmountException, InsufficientFundsException {
            if (amount <= 0) {
                throw new InvalidAmountException("Withdraw amount should be more than 0");
            }
            if (amount > balance) {
                throw new InsufficientFundsException("Insufficient Balance");
            }
            balance -= amount;
        }

        public void show() {
            System.out.printf("Account: %d | Balance: %.2f\n", accountNo, balance);
        }
    }
}
