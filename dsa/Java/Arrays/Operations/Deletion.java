public class Deletion {

    public static int[] deleteFromIndex(int target, int[] arr) {
        int[] newArr = new int[arr.length - 1];

        int trackingIndex = 0;

        for (int i = 0; i < arr.length; i++) {
            if (i == target) {
                continue;
            } else {
                newArr[trackingIndex] = arr[i];
                trackingIndex++;
            }

        }
        return newArr;
    }

    public static int[] deleteFirstOccurence(int target, int[] arr) {
        int[] newArr = new int[arr.length - 1];
        boolean found = false;
        int trackingIndex = 0;

        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target && !found) {
                found = true;
                continue;
            } else {
                newArr[trackingIndex] = arr[i];
                trackingIndex++;
            }
        }

        return newArr;
    }

    public static int[] deleteAllOccurences(int target, int[] arr) {
        int counter = 0;

        for (int i : arr) {
            if (i == target) {
                counter++;
            }
        }

        int[] newArr = new int[arr.length - counter];
        int trackingIndex = 0;

        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                continue;
            } else {
                newArr[trackingIndex] = arr[i];
                trackingIndex++;
            }
        }

        return newArr;
    }

    public static void main(String[] args) {
        int[] arr = { 1, 2, 3, 4, 5, 2 };
        int target = 2;
        int[] result = deleteAllOccurences(target, arr);
        for (int value : result) {
            System.out.println(value);
        }
    }
}
