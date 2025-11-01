public class Student extends Person {
    int rollNo;
    String course;
    float marks;
    String grade;

    Student(String name, String email, int rollNo, String course, float marks) {
        this.name = name;
        this.email = email;
        this.rollNo = rollNo;
        this.course = course;
        this.marks = marks;
        this.grade = this.GradeCalculator(marks);

    }

    private String GradeCalculator(float marks) {
        if (marks > 90.0) {
            return "O";
        } else if (marks > 85.0) {
            return "A+";
        } else if (marks > 80.0) {
            return "A";
        } else if (marks > 75.0) {
            return "B+";
        } else if (marks > 70.0) {
            return "B";
        } else if (marks > 60.0) {
            return "C";
        } else {
            return "F";
        }
    }

    void displayInfo() {
        System.out.printf("| %-10d | %-20s | %-25s | %-15s | %-10.2f | %-5s |\n",
                this.rollNo, this.name, this.email, this.course, this.marks, this.grade);
    }

    void setName(String name) {
        this.name = name;
    }

    void setEmail(String email) {
        this.email = email;
    }

    void setCourse(String course) {
        this.course = course;
    }

    void setMarks(float marks) {
        this.marks = marks;
    }
}
