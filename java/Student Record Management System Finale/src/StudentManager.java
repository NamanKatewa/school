import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class StudentManager implements RecordActions {

    private final List<Student> students;
    private final Map<Integer, Student> studentMap;
    private final Scanner scanner;

    public StudentManager(Scanner scanner) {
        this.scanner = scanner;
        this.students = new ArrayList<>();
        this.studentMap = new HashMap<>();

        List<Student> loaded = FileUtil.loadStudents();
        if (loaded != null) {
            for (Student s : loaded) {
                addToCollections(s);
            }
        }

        System.out.println(ConsoleColors.header("Loaded " + students.size() + " student(s) from file."));
        System.out.println();
    }

    private void addToCollections(Student s) {
        if (s == null) {
            return;
        }
        students.add(s);
        studentMap.put(s.getRollNo(), s);
    }

    private void showLoader(String message) {
        Thread t = new Thread(new Loader(message));
        t.start();
        try {
            t.join();
        } catch (InterruptedException e) {
        }
    }

    private int readInt(String prompt) {
        while (true) {
            System.out.print(ConsoleColors.prompt(prompt));
            String line = scanner.nextLine().trim();
            try {
                int value = Integer.parseInt(line);
                if (value <= 0) {
                    System.out.println(ConsoleColors.error("Roll number must be positive."));
                    continue;
                }
                return value;
            } catch (NumberFormatException e) {
                System.out.println(ConsoleColors.error("Invalid integer. Please try again."));
            }
        }
    }

    @Override
    public void addStudent() {
        System.out.println(ConsoleColors.header("\n--- Add Student ---"));

        int rollNo;
        while (true) {
            rollNo = readInt("Enter Roll No: ");
            if (studentMap.containsKey(rollNo)) {
                System.out.println(ConsoleColors.error("A student with this roll number already exists."));
            } else {
                break;
            }
        }

        Student s = new Student();
        s.setRollNo(rollNo);
        s.inputDetails(scanner);

        showLoader("Adding student, please wait");
        addToCollections(s);
        System.out.println(ConsoleColors.success("Student added successfully."));
    }

    @Override
    public void viewAllStudents() {
        System.out.println(ConsoleColors.header("\n--- View All Students ---"));
        if (students.isEmpty()) {
            System.out.println(ConsoleColors.error("No student records to display."));
            return;
        }

        Iterator<Student> iterator = students.iterator();
        while (iterator.hasNext()) {
            Student s = iterator.next();
            s.displayDetails();
        }
    }

    @Override
    public void searchStudent() {
        System.out.println(ConsoleColors.header("\n--- Search Student by Name ---"));
        if (students.isEmpty()) {
            System.out.println(ConsoleColors.error("No student records to search."));
            return;
        }

        System.out.print(ConsoleColors.prompt("Enter name to search: "));
        String name = scanner.nextLine().trim().toLowerCase();

        try {
            boolean found = false;
            for (Student s : students) {
                if (s.getName().toLowerCase().equals(name)) {
                    s.displayDetails();
                    found = true;
                }
            }
            if (!found) {
                throw new StudentNotFoundException("No student found with name: " + name);
            }
        } catch (StudentNotFoundException e) {
            System.out.println(ConsoleColors.error(e.getMessage()));
        }
    }

    @Override
    public void deleteStudent() {
        System.out.println(ConsoleColors.header("\n--- Delete Student by Name ---"));
        if (students.isEmpty()) {
            System.out.println(ConsoleColors.error("No student records to delete."));
            return;
        }

        System.out.print(ConsoleColors.prompt("Enter name to delete: "));
        String name = scanner.nextLine().trim().toLowerCase();

        boolean deletedAny = false;
        Iterator<Student> iterator = students.iterator();
        while (iterator.hasNext()) {
            Student s = iterator.next();
            if (s.getName().toLowerCase().equals(name)) {
                iterator.remove();
                studentMap.remove(s.getRollNo());
                deletedAny = true;
            }
        }

        if (deletedAny) {
            System.out.println(ConsoleColors.success("Student record(s) deleted successfully for name: " + name));
        } else {
            System.out.println(ConsoleColors.error("No student found with name: " + name));
        }
    }

    @Override
    public void updateStudent() {
        System.out.println(ConsoleColors.header("\n--- Update Student (by Roll No) ---"));
        if (students.isEmpty()) {
            System.out.println(ConsoleColors.error("No student records to update."));
            return;
        }

        int rollNo = readInt("Enter Roll No to update: ");

        try {
            Student s = studentMap.get(rollNo);
            if (s == null) {
                throw new StudentNotFoundException("No student found with roll number: " + rollNo);
            }

            System.out.println(ConsoleColors.header("Current details:"));
            s.displayDetails();

            System.out.println(ConsoleColors.prompt("Leave a field empty to keep the current value."));

            System.out.print(ConsoleColors.prompt("Enter new Name (current: " + s.getName() + "): "));
            String name = scanner.nextLine().trim();
            if (!name.isEmpty()) {
                s.setName(name);
            }

            System.out.print(ConsoleColors.prompt("Enter new Email (current: " + s.getEmail() + "): "));
            String email = scanner.nextLine().trim();
            if (!email.isEmpty()) {
                s.setEmail(email);
            }

            System.out.print(ConsoleColors.prompt("Enter new Course (current: " + s.getCourse() + "): "));
            String course = scanner.nextLine().trim();
            if (!course.isEmpty()) {
                s.setCourse(course);
            }

            System.out.print(ConsoleColors.prompt("Enter new Marks (current: " + s.getMarks() + ", blank to keep): "));
            String markLine = scanner.nextLine().trim();
            if (!markLine.isEmpty()) {
                try {
                    double newMarks = Double.parseDouble(markLine);
                    if (newMarks < 0 || newMarks > 100) {
                        System.out.println(
                                ConsoleColors.error("Marks must be between 0 and 100. Keeping previous value."));
                    } else {
                        s.setMarks(newMarks);
                    }
                } catch (NumberFormatException e) {
                    System.out.println(ConsoleColors.error("Invalid number. Keeping previous marks value."));
                }
            }

            System.out.println(ConsoleColors.success("Student updated successfully."));
        } catch (StudentNotFoundException e) {
            System.out.println(ConsoleColors.error(e.getMessage()));
        }
    }

    public void sortByMarksDescending() {
        System.out.println(ConsoleColors.header("\n--- Sort Students by Marks (Descending) ---"));
        if (students.isEmpty()) {
            System.out.println(ConsoleColors.error("No student records to sort."));
            return;
        }

        Comparator<Student> byMarksDesc = (s1, s2) -> Double.compare(s2.getMarks(), s1.getMarks());
        Collections.sort(students, byMarksDesc);

        System.out.println(ConsoleColors.header("Sorted Student List by Marks:"));
        Iterator<Student> iterator = students.iterator();
        while (iterator.hasNext()) {
            Student s = iterator.next();
            s.displayDetails();
        }
    }

    public void saveAndExit() {
        System.out.println();
        showLoader("Saving records to file, please wait");
        FileUtil.saveStudents(students);
        System.out.println(ConsoleColors.success("Saved and exiting."));
    }
}
