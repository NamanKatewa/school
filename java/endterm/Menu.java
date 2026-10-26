import java.util.Scanner;

public class Menu {

    static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("/n-- ARITHMETIC --");
        System.out.println("1. Add");
        System.out.println("2. Subtract");
        System.out.println("3. Divide");
        System.out.println("4. Multiply");
        System.out.println("5. Exit");
        System.out.print("Enter Choice: ");

        int op = sc.nextInt();

        System.out.print("Enter two numbers: ");
        double a = sc.nextDouble();
        double b = sc.nextDouble();

        switch (op) {
            case 1:
                System.out.println(a + b);
                break;
            case 2:
                System.out.println(a - b);
                break;
            case 3:
                if (b == 0) {
                    System.out.println("Cannot divide by zero");
                } else {
                    System.out.println(a / b);
                }
                break;
            case 4:
                System.out.println(a * b);
                break;
            case 5:
                sc.close();
                return;
            default:
                System.out.println("Invalid Choice");
        }
    }
}
