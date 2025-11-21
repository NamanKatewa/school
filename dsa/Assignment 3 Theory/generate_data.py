import csv
import random

FILENAME = "data.csv"

NUM_STUDENTS = 1000

NAMES = ["Aarav", "Vivaan", "Aditya", "Vihaan", "Arjun", "Sai", "Reyansh", "Ayaan", "Krishna", "Ishaan", "Shaurya"]
SURNAMES = ["Sharma", "Verma", "Gupta", "Malhotra", "Singh", "Patel", "Reddy", "Kumar", "Das", "Joshi"]
COURSES = ["CSE-101", "ECE-201", "MTH-301", "PHY-101", "HUM-101"]

def generate_data():
    print(f"Generating {NUM_STUDENTS} student records...")
    used_ids = set()

    with open(FILENAME, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["RollNumber", "Name", "Marks", "Course"])

        count = 0
        while count < NUM_STUDENTS:
            roll = random.randint(10000, 99999)
            if roll in used_ids:
                continue

            used_ids.add(roll)
            name = f"{random.choice(NAMES)} {random.choice(SURNAMES)}"
            marks = round(random.uniform(35.0, 100.0), 2)
            course = random.choice(COURSES)

            writer.writerow([roll, name, marks, course])
            count += 1

    print(f"Successfully created '{FILENAME}' with {NUM_STUDENTS} unique records.")

if __name__ == "__main__":
    generate_data()
