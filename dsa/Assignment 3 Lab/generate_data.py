import csv
import random

def generate_data(filename='data.csv', num_records=100):
    """
    Generates realistic sample student data and writes it to a CSV file.
    Each record includes StudentID, StudentName, Grade, and CourseDetails.
    """

    with open(filename, 'w', newline='') as csvfile:
        fieldnames = ['StudentID', 'StudentName', 'Grade', 'CourseDetails']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        
        used_ids = set()
        
        for i in range(num_records):
            student_id = random.randint(10000, 99999)
            while student_id in used_ids:
                student_id = random.randint(10000, 99999)
            used_ids.add(student_id)

            first_names = ["Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Heidi", "Ivan", "Judy"]
            last_names = ["Smith", "Jones", "Williams", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor", "Anderson"]
            student_name = f"{random.choice(first_names)} {random.choice(last_names)}"

            grade = round(random.uniform(50.0, 100.0), 2)

            courses = ["Math", "Physics", "Chemistry", "Biology", "Computer Science", "Literature", "History", "Art"]
            course_details = f"{random.choice(courses)} 10{random.randint(1, 4)}"

            writer.writerow({
                'StudentID': student_id,
                'StudentName': student_name,
                'Grade': grade,
                'CourseDetails': course_details
            })

if __name__ == '__main__':
    generate_data()
    print("Generated data.csv with 100 student records.")
