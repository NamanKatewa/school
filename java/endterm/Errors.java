public class Errors {
    public static void main(String[] args) {
        try {
            int x = 10 / 0;
            System.out.println(x);
        } catch (ArithmeticException e) {
            System.out.println("Division by Zero");
        } finally {
            System.out.println("Cleanup");
        }
    }

}
