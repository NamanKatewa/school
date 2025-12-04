public class Recursion {
    public static long factorial(int n) {
        if (n == 0) {
            return 1;
        }
        return n * factorial(n - 1);
    }

    public static long fibbonaci(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        return fibbonaci(n - 1) + fibbonaci(n - 2);
    }

    public static Node mergeSorted(Node a, Node b) {
        if (a == null) {
            return b;
        }

        if (b == null) {
            return a;
        }

        if (a.data <= b.data) {
            a.next = mergeSorted(a.next, b);
            return a;
        } else {
            b.next = mergeSorted(a, b.next);
            return b;
        }
    }
}
