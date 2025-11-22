import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class StudentManager {

    private List<Student> students;
    private Map<Integer, Student> studentMap;

    public StudentManager() {
        this.students = new ArrayList<>();
        this.studentMap = new HashMap<>();

        List<Student> loaded = FileUtil.loadStudents();
        if (loaded != null) {
            for (Student s : loaded) {
                addToCollections(s);
            }
        }

        if (students.isEmpty()) {
            System.out.println("No students loaded from file.");
        } else {
            System.out.println("Loaded " + students.size() + " students from file.");
        }
    }

    private void addToCollections(Student s) {
        if (s == null) {
            return;
        }
        students.add(s);
        studentMap.put(s.getRollNo(), s);
    }

    public void addStudent(Scanner sc) {
        System.out.print("Enter Roll No: ");
        int rollNo = readInt(sc);

        System.out.print("Enter Name: ");
        String name = sc.nextLine().trim();

        System.out.print("Enter Email: ");
        String email = sc.nextLine().trim();

        System.out.print("Enter Course: ");
        String course = sc.nextLine().trim();

        System.out.print("Enter Marks: ");
        double marks = readDouble(sc);

        Student s = new Student(rollNo, name, email, course, marks);
        addToCollections(s);
        System.out.println("Student added successfully.");
    }

    public void viewAllStudents() {
        if (students.isEmpty()) {
            System.out.println("No student records to display.");
            return;
        }
        System.out.println("=== All Students ===");
        Iterator<Student> iterator = students.iterator();
        while (iterator.hasNext()) {
            Student s = iterator.next();
            s.printDetails();
        }
    }

    public void searchByName(Scanner sc) {
        if (students.isEmpty()) {
            System.out.println("No student records to search.");
            return;
        }
        System.out.print("Enter name to search: ");
        String target = sc.nextLine().trim().toLowerCase();

        boolean found = false;
        System.out.println("Search Results:");
        for (Student s : students) {
            if (s.getName().toLowerCase().equals(target)) {
                s.printDetails();
                found = true;
            }
        }
        if (!found) {
            System.out.println("No student found with name: " + target);
        }
    }

    public void deleteByName(Scanner sc) {
        if (students.isEmpty()) {
            System.out.println("No student records to delete.");
            return;
        }
        System.out.print("Enter name to delete: ");
        String target = sc.nextLine().trim().toLowerCase();

        boolean deletedAny = false;
        Iterator<Student> iterator = students.iterator();
        while (iterator.hasNext()) {
            Student s = iterator.next();
            if (s.getName().toLowerCase().equals(target)) {
                iterator.remove();
                studentMap.remove(s.getRollNo());
                deletedAny = true;
            }
        }
        if (deletedAny) {
            System.out.println("Deleted student(s) with name: " + target);
        } else {
            System.out.println("No student found with name: " + target);
        }
    }

    public void sortByMarks() {
        if (students.isEmpty()) {
            System.out.println("No student records to sort.");
            return;
        }
        Comparator<Student> byMarks = new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return Double.compare(s1.getMarks(), s2.getMarks());
            }
        };

        Collections.sort(students, byMarks);

        System.out.println("Sorted Student List by Marks:");
        for (Student s : students) {
            s.printDetails();
        }
    }

    public void sortByName() {
        if (students.isEmpty()) {
            System.out.println("No student records to sort.");
            return;
        }
        Collections.sort(students);

        System.out.println("Sorted Student List by Name:");
        for (Student s : students) {
            s.printDetails();
        }
    }

    public void saveAndExit() {
        FileUtil.saveStudents(students);
        System.out.println("Exiting program. Goodbye!");
    }

    private int readInt(Scanner sc) {
        while (true) {
            String line = sc.nextLine().trim();
            try {
                return Integer.parseInt(line);
            } catch (NumberFormatException ex) {
                System.out.print("Invalid integer. Please re-enter: ");
            }
        }
    }

    private double readDouble(Scanner sc) {
        while (true) {
            String line = sc.nextLine().trim();
            try {
                return Double.parseDouble(line);
            } catch (NumberFormatException ex) {
                System.out.print("Invalid number. Please re-enter: ");
            }
        }
    }
}
