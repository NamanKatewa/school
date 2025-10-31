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
        System.out.printf("\u001B[33mEnter student name: \u001B[0m");
        String name = sc.nextLine();

        System.out.printf("\u001B[33mEnter student email: \u001B[0m");
        String email = sc.nextLine();

        System.out.printf("\u001B[33mEnter student course: \u001B[0m");
        String course = sc.nextLine();

        System.out.printf("\u001B[33mEnter student marks: \u001B[0m");
        float marks = sc.nextFloat();
        sc.nextLine();

        Student student = new Student(name, email, ++count, course, marks);
        students.put(count, student);

        System.out.printf("\u001B[32mStudent with roll no. %d added successfully!\u001B[0m\n\n", count);
    }

    @Override
    public void deleteStudent() {
        System.out.printf("\u001B[33mEnter roll number to delete: \u001B[0m");
        int rollNo = sc.nextInt();
        sc.nextLine();

        if (students.containsKey(rollNo)) {
            students.remove(rollNo);
            System.out.printf("\u001B[32mStudent with roll no. %d deleted.\u001B[0m\n\n", rollNo);
        } else {
            System.out.printf("\u001B[31mNo student found with roll no. %d\u001B[0m\n\n", rollNo);
        }
    }

    @Override
    public void updateStudent() {
        System.out.printf("\u001B[33mEnter roll number to update: \u001B[0m");
        int rollNo = sc.nextInt();
        sc.nextLine();

        Student student = students.get(rollNo);
        if (student == null) {
            System.out.printf("\u001B[31mNo student found with roll no. %d\u001B[0m\n\n", rollNo);
            return;
        }

        System.out.printf("\u001B[36mCurrent details:\u001B[0m\n");
        student.displayInfo();

        System.out.printf("\u001B[33mEnter new name (press Enter to skip): \u001B[0m");
        String newName = sc.nextLine();
        if (!newName.isEmpty())
            student.setName(newName);

        System.out.printf("\u001B[33mEnter new email (press Enter to skip): \u001B[0m");
        String newEmail = sc.nextLine();
        if (!newEmail.isEmpty())
            student.setEmail(newEmail);

        System.out.printf("\u001B[33mEnter new course (press Enter to skip): \u001B[0m");
        String newCourse = sc.nextLine();
        if (!newCourse.isEmpty())
            student.setCourse(newCourse);

        System.out.printf("\u001B[33mEnter new marks (-1 to skip): \u001B[0m");
        float newMarks = sc.nextFloat();
        sc.nextLine();
        if (newMarks >= 0)
            student.setMarks(newMarks);

        System.out.printf("\u001B[32mStudent details updated successfully!\u001B[0m\n\n");
    }

    @Override
    public void searchStudent() {
        System.out.printf("\u001B[33mEnter roll number to search: \u001B[0m");
        int rollNo = sc.nextInt();
        sc.nextLine();

        Student student = students.get(rollNo);
        if (student != null) {
            System.out.printf("\u001B[36mStudent Found:\u001B[0m\n");
            student.displayInfo();
        } else {
            System.out.printf("\u001B[31mNo student found with roll no. %d\u001B[0m\n\n", rollNo);
        }
    }

    public void viewAllStudents() {
        if (students.isEmpty()) {
            System.out.printf("\u001B[31mNo students to display.\u001B[0m\n\n");
            return;
        }

        System.out.printf("\n\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");
        System.out.printf("\u001B[36m|                                     All Students                                         |\u001B[0m\n");
        System.out.printf("\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");
        System.out.printf("\u001B[34m| %-10s | %-20s | %-25s | %-15s | %-10s | %-5s |\u001B[0m\n", "Roll No", "Name", "Email", "Course", "Marks", "Grade");
        System.out.printf("\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");

        for (Student s : students.values()) {
            s.displayInfo();
        }
        System.out.printf("\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");
        System.out.printf("\n");
    }

    @Override
    public void sortStudents() {
        if (students.isEmpty()) {
            System.out.printf("\u001B[31mNo students to sort.\u001B[0m\n\n");
            return;
        }

        System.out.printf("\u001B[36mSort by:\u001B[0m\n");
        System.out.printf("\u001B[36m1. Name\u001B[0m\n");
        System.out.printf("\u001B[36m2. Roll No\u001B[0m\n");
        System.out.printf("\u001B[36m3. Marks\u001B[0m\n");
        System.out.printf("\u001B[32mEnter your choice: \u001B[0m");

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
                System.out.printf("\u001B[31mInvalid choice.\u001B[0m\n");
                return;
        }

        System.out.printf("\n\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");
        System.out.printf("\u001B[36m|                                     Sorted Students                                        |\u001B[0m\n");
        System.out.printf("\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");
        System.out.printf("\u001B[34m| %-10s | %-20s | %-25s | %-15s | %-10s | %-5s |\u001B[0m\n", "Roll No", "Name", "Email", "Course", "Marks", "Grade");
        System.out.printf("\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");

        for (Student s : studentList) {
            s.displayInfo();
        }
        System.out.printf("\u001B[36m+----------------------------------------------------------------------------------------------------+\u001B[0m\n");
        System.out.printf("\n");
    }



    public void closeScanner() {
        sc.close();
    }
}
