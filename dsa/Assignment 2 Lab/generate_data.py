import csv
import random

def generate_data(file_path="data.csv", num_records=10):
    """Generates sample ticket data and saves it to a CSV file."""
    fieldnames = ["ticketID", "customerName", "issueDescription", "priority"]
    
    with open(file_path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)

        for i in range(1, num_records + 1):
            writer.writerow({
                "ticketID": i,
                "customerName": f"Customer {i}",
                "issueDescription": f"Issue Description {random.randint(1, 100)}",
                "priority": random.randint(1, 3)
            })
    print(f"Generated {num_records} records in {file_path}")

if __name__ == "__main__":
    generate_data()
