import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StudentManager manager = new StudentManager();

        int choice;
        do {
            printMenu();
            choice = readInt(sc, "Enter choice: ");

            switch (choice) {
                case 1:
                    manager.addStudent(sc);
                    break;
                case 2:
                    manager.viewAllStudents();
                    break;
                case 3:
                    manager.searchByName(sc);
                    break;
                case 4:
                    manager.deleteByName(sc);
                    break;
                case 5:
                    manager.sortByMarks();
                    break;
                case 6:
                    manager.saveAndExit();
                    break;
                case 7:
                    manager.sortByName();
                    break;
                default:
                    System.out.println("Invalid choice. Please select again.");
            }

            if (choice != 6) {
                System.out.println();
            }
        } while (choice != 6);

        sc.close();
    }

    private static void printMenu() {
        System.out.println("===== Capstone Student Menu =====");
        System.out.println("1. Add Student");
        System.out.println("2. View All Students");
        System.out.println("3. Search by Name");
        System.out.println("4. Delete by Name");
        System.out.println("5. Sort by Marks");
        System.out.println("6. Save and Exit");
        System.out.println("7. Sort by Name (Optional)");
    }

    private static int readInt(Scanner sc, String prompt) {
        System.out.print(prompt);
        while (true) {
            String line = sc.nextLine().trim();
            try {
                return Integer.parseInt(line);
            } catch (NumberFormatException ex) {
                System.out.print("Invalid integer. Please re-enter: ");
            }
        }
    }
}
