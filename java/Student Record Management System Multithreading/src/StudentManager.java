import java.util.Map;
import java.util.HashMap;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class StudentManager implements RecordActions {

    Map<Integer, Student> students = new HashMap<>();
    int count = 0;
    Scanner sc = new Scanner(System.in);

    @Override
    public void addStudent() {
        System.out.printf(Constants.ANSI_YELLOW + "Enter student name: " + Constants.ANSI_RESET);
        String name = sc.nextLine();

        System.out.printf(Constants.ANSI_YELLOW + "Enter student email: " + Constants.ANSI_RESET);
        String email = sc.nextLine();

        System.out.printf(Constants.ANSI_YELLOW + "Enter student course: " + Constants.ANSI_RESET);
        String course = sc.nextLine();

        System.out.printf(Constants.ANSI_YELLOW + "Enter student marks: " + Constants.ANSI_RESET);
        float marks = 0;
        try {
            marks = sc.nextFloat();
        } catch (java.util.InputMismatchException e) {
            System.out.printf(Constants.ANSI_RED + "Invalid input. Please enter a number for marks."
                    + Constants.ANSI_RESET + "\n");
            sc.nextLine();
            return;
        }
        sc.nextLine();

        Student student = new Student(name, email, ++count, course, marks);
        students.put(count, student);

        System.out.printf(
                Constants.ANSI_GREEN + "Student with roll no. %d added successfully!" + Constants.ANSI_RESET + "\n\n",
                count);
    }

    @Override
    public void deleteStudent() throws StudentNotFoundException {
        System.out.printf(Constants.ANSI_YELLOW + "Enter roll number to delete: " + Constants.ANSI_RESET);
        int rollNo = 0;
        try {
            rollNo = sc.nextInt();
        } catch (java.util.InputMismatchException e) {
            System.out.printf(Constants.ANSI_RED + "Invalid input. Please enter a number for roll number."
                    + Constants.ANSI_RESET + "\n");
            sc.nextLine();
            return;
        }
        sc.nextLine();

        if (students.containsKey(rollNo)) {
            students.remove(rollNo);
            System.out.printf(
                    Constants.ANSI_GREEN + "Student with roll no. %d deleted." + Constants.ANSI_RESET + "\n\n", rollNo);
        } else {
            throw new StudentNotFoundException("No student found with roll no. " + rollNo);
        }
    }

    @Override
    public void updateStudent() throws StudentNotFoundException {
        System.out.printf(Constants.ANSI_YELLOW + "Enter roll number to update: " + Constants.ANSI_RESET);
        int rollNo = 0;
        try {
            rollNo = sc.nextInt();
        } catch (java.util.InputMismatchException e) {
            System.out.printf(Constants.ANSI_RED + "Invalid input. Please enter a number for roll number."
                    + Constants.ANSI_RESET + "\n");
            sc.nextLine();
            return;
        }
        sc.nextLine();

        Student student = students.get(rollNo);
        if (student == null) {
            throw new StudentNotFoundException("No student found with roll no. " + rollNo);
        }

        System.out.printf(Constants.ANSI_CYAN + "Current details:" + Constants.ANSI_RESET + "\n");
        student.displayInfo();

        System.out.printf(Constants.ANSI_YELLOW + "Enter new name (press Enter to skip): " + Constants.ANSI_RESET);
        String newName = sc.nextLine();
        if (!newName.isEmpty())
            student.setName(newName);

        System.out.printf(Constants.ANSI_YELLOW + "Enter new email (press Enter to skip): " + Constants.ANSI_RESET);
        String newEmail = sc.nextLine();
        if (!newEmail.isEmpty())
            student.setEmail(newEmail);

        System.out.printf(Constants.ANSI_YELLOW + "Enter new course (press Enter to skip): " + Constants.ANSI_RESET);
        String newCourse = sc.nextLine();
        if (!newCourse.isEmpty())
            student.setCourse(newCourse);

        System.out.printf(Constants.ANSI_YELLOW + "Enter new marks (-1 to skip): " + Constants.ANSI_RESET);
        float newMarks = 0;
        try {
            newMarks = sc.nextFloat();
        } catch (java.util.InputMismatchException e) {
            System.out.printf(Constants.ANSI_RED + "Invalid input. Please enter a number for marks."
                    + Constants.ANSI_RESET + "\n");
            sc.nextLine();
            return;
        }
        sc.nextLine();
        if (newMarks >= 0)
            student.setMarks(newMarks);

        System.out
                .printf(Constants.ANSI_GREEN + "Student details updated successfully!" + Constants.ANSI_RESET + "\n\n");
    }

    @Override
    public void searchStudent() throws StudentNotFoundException {
        System.out.printf(Constants.ANSI_YELLOW + "Enter roll number to search: " + Constants.ANSI_RESET);
        int rollNo = 0;
        try {
            rollNo = sc.nextInt();
        } catch (java.util.InputMismatchException e) {
            System.out.printf(Constants.ANSI_RED + "Invalid input. Please enter a number for roll number."
                    + Constants.ANSI_RESET + "\n");
            sc.nextLine();
            return;
        }
        sc.nextLine();

        Student student = students.get(rollNo);
        if (student != null) {
            System.out.printf(Constants.ANSI_CYAN + "Student Found:" + Constants.ANSI_RESET + "\n");
            student.displayInfo();
        } else {
            throw new StudentNotFoundException("No student found with roll no. " + rollNo);
        }
    }

    public void viewAllStudents() {
        if (students.isEmpty()) {
            System.out.printf(Constants.ANSI_RED + "No students to display." + Constants.ANSI_RESET + "\n\n");
            return;
        }

        System.out.printf("\n" + Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN
                + "|                                     All Students                                         |"
                + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");
        System.out.printf(
                Constants.ANSI_BLUE + "| %-10s | %-20s | %-25s | %-15s | %-10s | %-5s |" + Constants.ANSI_RESET + "\n",
                "Roll No", "Name", "Email", "Course", "Marks", "Grade");
        System.out.printf(Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");

        for (Student s : students.values()) {
            s.displayInfo();
        }
        System.out.printf(Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");
        System.out.printf("\n");
    }

    @Override
    public void sortStudents() {
        if (students.isEmpty()) {
            System.out.printf(Constants.ANSI_RED + "No students to sort." + Constants.ANSI_RESET + "\n\n");
            return;
        }

        System.out.printf(Constants.ANSI_CYAN + "Sort by:" + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN + "1. Name" + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN + "2. Roll No" + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN + "3. Marks" + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_GREEN + "Enter your choice: " + Constants.ANSI_RESET);

        int choice = sc.nextInt();
        sc.nextLine();

        ArrayList<Student> studentList = new ArrayList<>(students.values());

        switch (choice) {
            case 1:
                Collections.sort(studentList, Comparator.comparing(s -> s.name));
                break;
            case 2:
                Collections.sort(studentList, Comparator.comparing(s -> s.rollNo));
                break;
            case 3:
                Collections.sort(studentList, Comparator.comparing(s -> s.marks));
                break;
            default:
                System.out.printf(Constants.ANSI_RED + "Invalid choice." + Constants.ANSI_RESET + "\n");
                return;
        }

        System.out.printf("\n" + Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN
                + "|                                     Sorted Students                                        |"
                + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");
        System.out.printf(
                Constants.ANSI_BLUE + "| %-10s | %-20s | %-25s | %-15s | %-10s | %-5s |" + Constants.ANSI_RESET + "\n",
                "Roll No", "Name", "Email", "Course", "Marks", "Grade");
        System.out.printf(Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");

        for (Student s : studentList) {
            s.displayInfo();
        }
        System.out.printf(Constants.ANSI_CYAN
                + "+----------------------------------------------------------------------------------------------------+"
                + Constants.ANSI_RESET + "\n");
        System.out.printf("\n");
    }

    public void closeScanner() {
        sc.close();
    }
}
