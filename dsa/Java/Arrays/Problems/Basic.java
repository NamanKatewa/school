
public class Basic {

    public static void printAlternate(int[] arr) {
        for (int i = 0; i < arr.length; i += 2) {
            System.out.printf("%d, ", arr[i]);
        }
    }

    public static void main(String[] args) {
        int[] arr = { 10, 20, 30, 40, 50 };
        printAlternate(arr);
    }
}
