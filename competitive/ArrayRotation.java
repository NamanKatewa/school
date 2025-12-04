public class ArrayRotation {
    private static void rotateLeftBrute(int[] arr, int k) {
        int n = arr.length;
        if (n == 0) {
            return;
        }

        k %= n;

        for (int step = 0; step < k; step++) {
            int first = arr[0];

            for (int i = 0; i < n - 1; i++) {
                arr[i] = arr[i + 1];
            }
            arr[n - 1] = first;
        }
    }

    private static void rotateRightBrute(int[] arr, int k) {
        int n = arr.length;
        if (n == 0) {
            return;
        }
        k %= n;

        for (int step = 0; step < k; step++) {
            int last = arr[n - 1];
            for (int i = n - 1; i > 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = last;
        }
    }
}
