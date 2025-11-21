import csv
import random

PATIENT_FILENAME = "data.csv"
INVENTORY_FILENAME = "inventory.txt"
NUM_PATIENTS = 50

NAMES = [
    "Aarav", "Vihaan", "Aditya", "Sai", "Arjun", "Reyansh", "Muhammad", "Krishna",
    "Ishaan", "Shaurya", "Anaya", "Myra", "Aadhya", "Saanvi", "Kiara", "Fatima",
    "Amaya", "Zoya", "Diya", "Riya"
]

SURNAMES = [
    "Sharma", "Verma", "Patel", "Singh", "Kumar", "Das", "Gupta", "Reddy",
    "Rao", "Nair", "Iyer", "Khan", "Ahmed", "Joshi", "Mehta", "Malhotra"
]

TREATMENTS = [
    "General Checkup", "Cardiac Surgery", "Orthopedic Casting", "Viral Fever Treatment",
    "Dengue Treatment", "X-Ray Analysis", "MRI Scan", "Blood Test"
]

def generate_patient_data():
    print(f"Generating {NUM_PATIENTS} patient records...")
    with open(PATIENT_FILENAME, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["PatientID", "Name", "AdmissionDate", "Treatment", "Priority"])

        for i in range(1, NUM_PATIENTS + 1):
            name = f"{random.choice(NAMES)} {random.choice(SURNAMES)}"
            date = f"{random.randint(1, 30)}/09/2025"
            treatment = random.choice(TREATMENTS)
            priority = random.randint(1, 5)

            writer.writerow([1000 + i, name, date, treatment, priority])

    print(f"Saved to {PATIENT_FILENAME}")

def generate_inventory_data():
    print("Generating inventory calculation tasks (Postfix)...")
    expressions = [
        "10 20 +",
        "50 5 2 * -",
        "100 20 / 5 +",
        "5 6 * 10 +",
        "200 10 / 5 2 * +"
    ]

    with open(INVENTORY_FILENAME, mode='w', encoding='utf-8') as file:
        for expr in expressions:
            file.write(expr + "\n")

    print(f"Saved to {INVENTORY_FILENAME}")

if __name__ == "__main__":
    generate_patient_data()
    generate_inventory_data()
