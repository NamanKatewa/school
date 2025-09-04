import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Transaction {
    private final TransactionType type;
    private final double amount;
    private final LocalDateTime timestamp;

    public Transaction(TransactionType type, double amount) {
        this.type = type;
        this.amount = amount;
        this.timestamp = LocalDateTime.now();
    }

    @Override
    public String toString() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return String.format("Timestamp: %s, Type: %s, Amount: %.2f",
                timestamp.format(formatter), type, amount);
    }
}