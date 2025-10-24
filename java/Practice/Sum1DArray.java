public class Sum1DArray {

    public static void main(String[] args) {
        int[] array = { 1, 2, 3, 4, 5 };
        int sum = 0;
        for (int x = 0; x < array.length; x++) {
            sum += array[x];
        }

        System.out.println(sum);
    }
}