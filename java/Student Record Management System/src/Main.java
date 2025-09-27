import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Student> students = new ArrayList<>();

        while (true) {
            System.out.println("\n===== Student Record Menu =====");
            System.out.println("1. Add Student");
            System.out.println("2. Display All Students");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    Student newStudent = new Student();
                    newStudent.inputDetails();
                    students.add(newStudent);
                    System.out.println("Student added successfully.");
                    break;
                case 2:
                    if (students.isEmpty()) {
                        System.out.println("No student records to display.");
                    } else {
                        for (Student student : students) {
                            student.displayDetails();
                            System.out.println();
                        }
                    }
                    break;
                case 3:
                    System.out.println("Exiting the application. Goodbye!");
                    scanner.close();
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
