public class Avg1DArray {
    public static void main(String[] args) {
        int[] array = { 10, 15, 5, 20, 25, 30 };

        int sum = 0;

        for (int x = 0; x < array.length; x++) {
            sum += array[x];
        }
        float avg = sum / array.length;

        System.out.println(avg);
    }
}
