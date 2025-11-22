import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StudentManager manager = new StudentManager(scanner);

        int choice;
        do {
            printMenu();
            choice = readInt(scanner, "Enter choice: ");

            switch (choice) {
                case 1:
                    manager.addStudent();
                    break;
                case 2:
                    manager.viewAllStudents();
                    break;
                case 3:
                    manager.searchStudent();
                    break;
                case 4:
                    manager.deleteStudent();
                    break;
                case 5:
                    manager.sortByMarksDescending();
                    break;
                case 6:
                    manager.updateStudent();
                    break;
                case 7:
                    manager.saveAndExit();
                    break;
                default:
                    System.out.println(ConsoleColors.error("Invalid choice. Please select a valid option."));
            }

            if (choice != 7) {
                System.out.println();
            }
        } while (choice != 7);

        scanner.close();
    }

    private static void printMenu() {
        System.out.println(ConsoleColors.header("===== Capstone Student Menu ====="));
        System.out.println(ConsoleColors.GREEN_BOLD + "1. Add Student" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "2. View All Students" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "3. Search by Name" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "4. Delete by Name" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "5. Sort by Marks (Desc)" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "6. Update Student (by Roll No)" + ConsoleColors.RESET);
        System.out.println(ConsoleColors.GREEN_BOLD + "7. Save and Exit" + ConsoleColors.RESET);
    }

    private static int readInt(Scanner scanner, String prompt) {
        while (true) {
            System.out.print(ConsoleColors.prompt(prompt));
            String line = scanner.nextLine().trim();
            try {
                return Integer.parseInt(line);
            } catch (NumberFormatException e) {
                System.out.println(ConsoleColors.error("Invalid integer. Please try again."));
            }
        }
    }
}
