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
        System.out.printf(Constants.ANSI_YELLOW + "Press Enter to continue..." + Constants.ANSI_RESET);
        try {
            System.in.read();
        } catch (Exception e) {
        }
    }

    public static void main(String[] args) {

        StudentManager sm = new StudentManager();
        Scanner sc = new Scanner(System.in);

        System.out.printf(Constants.ANSI_YELLOW + "+------------------------------------+" + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_YELLOW + "|    STUDENT MANAGEMENT SYSTEM     |" + Constants.ANSI_RESET + "\n");
        System.out.printf(Constants.ANSI_YELLOW + "+------------------------------------+" + Constants.ANSI_RESET + "\n");

        boolean running = true;

        while (running) {
            clearScreen();
            System.out.printf(Constants.ANSI_CYAN + "1. Add a new student" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_CYAN + "2. Delete a student" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_CYAN + "3. Update details of a student" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_CYAN + "4. Search for a student" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_CYAN + "5. View all students" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_CYAN + "6. Sort students" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_RED + "7. Exit" + Constants.ANSI_RESET + "\n");
            System.out.printf(Constants.ANSI_GREEN + "What do you want to do: " + Constants.ANSI_RESET);

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
                    System.out.printf(Constants.ANSI_RED + "Enter a valid choice" + Constants.ANSI_RESET + "\n");
                    pressEnterToContinue();
            }
        }

        sc.close();

        System.out.printf(Constants.ANSI_RED + "Exiting..." + Constants.ANSI_RESET);
    }
}
