import java.util.Scanner;

public class Student extends Person {
    long rollNo;
    String course;
    double marks;
    char grade;

    public Student() {
        super();
        this.rollNo = 0;
        this.course = "";
        this.marks = 0.0;
        this.grade = ' ';
    }

    public Student(long rollNo, String name, String course, double marks) {
        super(name);
        this.rollNo = rollNo;
        this.course = course;
        this.marks = marks;
        this.calculateGrade();
    }

    public void inputDetails() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter Roll No: ");
        this.rollNo = scanner.nextLong();
        scanner.nextLine(); // Consume newline
        System.out.print("Enter Name: ");
        this.name = scanner.nextLine();
        System.out.print("Enter Course: ");
        this.course = scanner.nextLine();
        System.out.print("Enter Marks: ");
        this.marks = scanner.nextDouble();
        while (this.marks < 0 || this.marks > 100) {
            System.out.println("Invalid marks. Please enter a value between 0 and 100.");
            System.out.print("Enter Marks: ");
            this.marks = scanner.nextDouble();
        }
        this.calculateGrade();
    }

    public void displayDetails() {
        System.out.println("Roll No: " + this.rollNo);
        System.out.println("Name: " + this.name);
        System.out.println("Course: " + this.course);
        System.out.println("Marks: " + this.marks);
        System.out.println("Grade: " + this.grade);
    }

    public void calculateGrade() {
        if (this.marks >= 90) {
            this.grade = 'A';
        } else if (this.marks >= 80) {
            this.grade = 'B';
        } else if (this.marks >= 70) {
            this.grade = 'C';
        } else if (this.marks >= 60) {
            this.grade = 'D';
        } else {
            this.grade = 'F';
        }
    }
}
