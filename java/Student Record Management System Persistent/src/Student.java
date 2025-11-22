import java.text.DecimalFormat;

public class Student implements Comparable<Student> {
    private int rollNo;
    private String name;
    private String email;
    private String course;
    private double marks;

    private static final String DELIMITER = ",";

    public Student(int rollNo, String name, String email, String course, double marks) {
        this.rollNo = rollNo;
        this.name = name;
        this.email = email;
        this.course = course;
        this.marks = marks;
    }

    public int getRollNo() {
        return rollNo;
    }

    public void setRollNo(int rollNo) {
        this.rollNo = rollNo;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
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
    }

    @Override
    public int compareTo(Student other) {
        if (other == null) {
            return 1;
        }
        return this.name.toLowerCase().compareTo(other.name.toLowerCase());
    }

    public String toFileString() {
        String safeName = name.replace(DELIMITER, " ");
        String safeEmail = email.replace(DELIMITER, " ");
        String safeCourse = course.replace(DELIMITER, " ");

        DecimalFormat df = new DecimalFormat("#.##");
        return rollNo + DELIMITER
                + safeName + DELIMITER
                + safeEmail + DELIMITER
                + safeCourse + DELIMITER
                + df.format(marks);
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
        } catch (NumberFormatException ex) {
            return null;
        }
    }

    public void printDetails() {
        System.out.println("Roll No: " + rollNo);
        System.out.println("Name: " + name);
        System.out.println("Email: " + email);
        System.out.println("Course: " + course);
        System.out.println("Marks: " + marks);
        System.out.println();
    }

    @Override
    public String toString() {
        return "Student{" +
                "rollNo=" + rollNo +
                ", name='" + name + '\'' +
                ", email='" + email + '\'' +
                ", course='" + course + '\'' +
                ", marks=" + marks +
                '}';
    }
}
