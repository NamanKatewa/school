class Traversal {

    public static void main(String[] args) {
        int[] arr = { 1, 2, 3, 4, 5 };

        System.out.println("Linear Traversal:");
        for (int i = 0; i < arr.length; i++) {
            System.out.printf("%d, ", arr[i]);
        }

        System.out.println("");

        System.out.println("Reverse Traversal:");
        for (int i = arr.length - 1; i >= 0; i--) {
            System.out.printf("%d, ", arr[i]);
        }

        System.out.println("");

        System.out.println("For Each:");
        for (int value : arr) {
            System.out.printf("%d, ", value);
        }
    }
}