import java.util.ArrayList;
import java.util.Collections;

public class Basic {

    public static void printAlternate(int[] arr) {
        for (int i = 0; i < arr.length; i += 2) {
            System.out.printf("%d, ", arr[i]);
        }
    }

    public static void leadersNaive(int[] arr) {
        ArrayList<Integer> result = new ArrayList<>();

        for (int x = 0; x < arr.length; x++) {
            int y;
            for (y = x + 1; y < arr.length; y++) {
                if (arr[y] > arr[x]) {
                    break;
                }
            }
            if (y == arr.length) {
                result.add(arr[x]);
            }
        }

        for (int x : result) {
            System.out.printf("%d, ", x);
        }
    }

    public static ArrayList<Integer> leadersOptimal(int[] arr) {
        ArrayList<Integer> result = new ArrayList<>();

        int max = arr[arr.length - 1];

        for (int i = arr.length - 1; i >= 0; i--) {
            if (arr[i] >= max) {
                max = arr[i];
                result.add(arr[i]);
            }
        }
        Collections.reverse(result);
        return result;

    }

    public static boolean isSorted(int[] arr) {
        for (int x = 0; x < arr.length - 2; x++) {
            if (arr[x + 1] < arr[x]) {
                return false;
            }
        }
        return true;
    }

    public static ArrayList<Integer> removeDuplicatesSorted(int[] arr) {
        ArrayList<Integer> result = new ArrayList<>();
        int prev = arr[0];
        result.add(arr[0]);

        for (int x = 1; x < arr.length; x++) {
            if (arr[x] == prev) {
                continue;
            } else {
                result.add(arr[x]);
                prev = arr[x];
            }
        }

        return result;
    }

    public static ArrayList<ArrayList<Integer>> subArrays(int[] arr) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();

        for (int i = 0; i < arr.length; i++) {

            for (int j = i; j < arr.length; j++) {
                ArrayList<Integer> sub = new ArrayList<>();

                for (int k = i; k <= j; k++) {
                    sub.add(arr[k]);
                }
                result.add(sub);
            }
        }

        return result;
    }

    public static int[] reverse(int[] arr) {
        int n = arr.length - 1;
        for (int i = 0; i < arr.length / 2; i++) {
            int temp = arr[n - i];
            arr[n - i] = arr[i];
            arr[i] = temp;
        }

        return arr;
    }

    public static int[] rotateClockwise(int[] arr) {
        int n = arr.length;
        int last = arr[n - 1];

        for (int i = n - 1; i > 0; i--) {
            arr[i] = arr[i - 1];
        }

        arr[0] = last;
        return arr;
    }

    public static int[] rotateAntiClockwise(int[] arr) {
        int n = arr.length;
        int first = arr[0];
        for (int i = 0; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[n - 1] = first;
        return arr;
    }

    public static int[] zeroesToEnd(int[] arr) {
        int count = 0;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] != 0) {
                arr[count++] = arr[i];
            }
        }

        for (int i = count; i < arr.length; i++) {
            arr[i] = 0;
        }
        return arr;
    }

    public static int minIncrementToEqual(int[] arr, int k) {
        int count = 0;
        int max = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        for (int x : arr) {
            if (((max - x) % k) != 0) {
                return -1;
            } else {
                count += (max - x) / k;
            }

        }

        return count;
    }

    public static void main(String[] args) {

        // int result = minCostToSizeOne(arr);
        // System.out.println(Arrays.toString(result));
        // System.out.println(result);
    }
}
