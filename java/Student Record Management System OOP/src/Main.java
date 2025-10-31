import java.util.Scanner;

public class Main {
    public static void clearScreen() {
        try {
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void pressEnterToContinue() {
        System.out.printf("\u001B[33mPress Enter to continue...\u001B[0m");
        try {
            System.in.read();
        } catch (Exception e) {
        }
    }

    public static void main(String[] args) {

        StudentManager sm = new StudentManager();
        Scanner sc = new Scanner(System.in);

        System.out.printf("\u001B[33m+------------------------------------+\u001B[0m\n");
        System.out.printf("\u001B[33m|    STUDENT MANAGEMENT SYSTEM     |\u001B[0m\n");
        System.out.printf("\u001B[33m+------------------------------------+\u001B[0m\n");

        boolean running = true;

        while (running) {
            clearScreen();
            System.out.printf("\u001B[36m1. Add a new student\u001B[0m\n");
            System.out.printf("\u001B[36m2. Delete a student\u001B[0m\n");
            System.out.printf("\u001B[36m3. Update details of a student\u001B[0m\n");
            System.out.printf("\u001B[36m4. Search for a student\u001B[0m\n");
            System.out.printf("\u001B[36m5. View all students\u001B[0m\n");
            System.out.printf("\u001B[36m6. Sort students\u001B[0m\n");
            System.out.printf("\u001B[31m7. Exit\u001B[0m\n");
            System.out.printf("\u001B[32mWhat do you want to do: \u001B[0m");

            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    sm.addStudent();
                    pressEnterToContinue();
                    break;
                case 2:
                    sm.deleteStudent();
                    pressEnterToContinue();
                    break;
                case 3:
                    sm.updateStudent();
                    pressEnterToContinue();
                    break;
                case 4:
                    sm.searchStudent();
                    pressEnterToContinue();
                    break;
                case 5:
                    sm.viewAllStudents();
                    pressEnterToContinue();
                    break;
                case 6:
                    sm.sortStudents();
                    pressEnterToContinue();
                    break;
                case 7:
                    running = false;
                    break;

                default:
                    System.out.printf("\u001B[31mEnter a valid choice\u001B[0m\n");
                    pressEnterToContinue();
            }
        }

        sc.close();

        System.out.printf("\u001B[31mExiting...\u001B[0m");
    }
}
