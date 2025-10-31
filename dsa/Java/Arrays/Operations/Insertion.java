import java.util.Arrays;

public class Insertion {

    public static int[] insertAtIndex(int target, int elem, int[] arr) {
        int[] newArr = new int[arr.length + 1];

        int trackingIndex = 0;

        for (int i = 0; i < newArr.length; i++) {
            if (i == target) {
                newArr[i] = elem;
            } else {
                newArr[i] = arr[trackingIndex];
                trackingIndex++;
            }

        }
        return newArr;
    }

    public static void main(String[] args) {
        int[] arr = { 1, 2, 3, 4, 5 };
        int elem = 6;
        int target = 3;
        int[] result = Insertion.insertAtIndex(target, elem, arr);
        System.out.println(Arrays.toString(result));

    }
}
