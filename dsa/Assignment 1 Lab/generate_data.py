import csv
import random

def generate_mock_data(num_items=50, filename="inventory_data.csv"):
    """
    Generates mock inventory data and saves it to a CSV file.
    Each item has an ID, Name, Quantity, and Price.
    """
    headers = ["itemID", "itemName", "quantity", "price"]
    data = []

    for i in range(1, num_items + 1):
        item_id = i
        item_name = f"Item_{i:03d}"
        quantity = random.randint(1, 200)
        price = round(random.uniform(0.5, 99.99), 2)
        data.append([item_id, item_name, quantity, price])

    with open(filename, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(headers)
        csv_writer.writerows(data)
    
    print(f"Generated {num_items} mock inventory items to {filename}")

if __name__ == "__main__":
    generate_mock_data()
