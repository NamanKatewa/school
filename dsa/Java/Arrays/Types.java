import java.util.ArrayList;

class Types {
    // Fixed
    // Cannot change the size
    int[] arr1 = new int[5];
    // Above is effectively same as below
    int[] arr2 = { 0, 0, 0, 0, 0 };

    // Dynamic
    // Normally assigned a size of 10
    // Increases with a scale of 2, but 1.5 in Java.
    ArrayList<Integer> arr3 = new ArrayList<>();

    // One Dimensional
    int[] arr4 = new int[5];

    // Two Dimensional
    int[][] arr5 = new int[5][4];

}