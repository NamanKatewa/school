import java.util.Scanner;

public class Student extends Person {
    private int rollNo;
    private String course;
    private double marks;
    private String grade;

    private static final String DELIMITER = ",";

    public Student() {
        super();
    }

    public Student(int rollNo, String name, String email, String course, double marks) {
        super(name, email);
        this.rollNo = rollNo;
        this.course = course;
        this.marks = marks;
        calculateGrade();
    }

    public int getRollNo() {
        return rollNo;
    }

    public void setRollNo(int rollNo) {
        this.rollNo = rollNo;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }

    public double getMarks() {
        return marks;
    }

    public void setMarks(double marks) {
        this.marks = marks;
        calculateGrade();
    }

    public String getGrade() {
        return grade;
    }

    public void inputDetails(Scanner scanner) {
        System.out.print(ConsoleColors.prompt("Enter Name: "));
        this.name = scanner.nextLine().trim();

        System.out.print(ConsoleColors.prompt("Enter Email: "));
        this.email = scanner.nextLine().trim();

        System.out.print(ConsoleColors.prompt("Enter Course: "));
        this.course = scanner.nextLine().trim();

        double m;
        while (true) {
            System.out.print(ConsoleColors.prompt("Enter Marks (0-100): "));
            String line = scanner.nextLine().trim();
            try {
                m = Double.parseDouble(line);
                if (m < 0 || m > 100) {
                    System.out.println(ConsoleColors.error("Marks must be between 0 and 100."));
                    continue;
                }
                break;
            } catch (NumberFormatException e) {
                System.out.println(ConsoleColors.error("Invalid number. Please re-enter marks."));
            }
        }
        this.marks = m;
        calculateGrade();
    }

    public void calculateGrade() {
        if (marks >= 90) {
            grade = "A";
        } else if (marks >= 80) {
            grade = "B";
        } else if (marks >= 70) {
            grade = "C";
        } else if (marks >= 60) {
            grade = "D";
        } else {
            grade = "F";
        }
    }

    @Override
    public void displayInfo() {
        System.out.println(ConsoleColors.CYAN_BOLD + "Name: " + name + ConsoleColors.RESET);
        System.out.println(ConsoleColors.CYAN_BOLD + "Email: " + email + ConsoleColors.RESET);
    }

    public void displayDetails() {
        System.out.println(ConsoleColors.BLUE_BOLD + "----------------------------" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "Roll No: " + rollNo + ConsoleColors.RESET);
        displayInfo();
        System.out.println(ConsoleColors.GREEN_BOLD + "Course: " + course + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "Marks: " + marks + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "Grade: " + grade + ConsoleColors.RESET);
        System.out.println(ConsoleColors.BLUE_BOLD + "----------------------------" + ConsoleColors.RESET);
    }

    public String toFileString() {
        String safeName = name.replace(DELIMITER, " ");
        String safeEmail = email.replace(DELIMITER, " ");
        String safeCourse = course.replace(DELIMITER, " ");
        return rollNo + DELIMITER + safeName + DELIMITER
                + safeEmail + DELIMITER + safeCourse + DELIMITER + marks;
    }

    public static Student fromFileString(String line) {
        if (line == null || line.trim().isEmpty()) {
            return null;
        }
        String[] parts = line.split(DELIMITER);
        if (parts.length != 5) {
            return null;
        }
        try {
            int roll = Integer.parseInt(parts[0].trim());
            String name = parts[1].trim();
            String email = parts[2].trim();
            String course = parts[3].trim();
            double marks = Double.parseDouble(parts[4].trim());
            return new Student(roll, name, email, course, marks);
        } catch (NumberFormatException e) {
            return null;
        }
    }
}
