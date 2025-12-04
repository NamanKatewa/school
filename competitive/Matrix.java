public class Matrix {
    private static void transpose(int[][] a) {
        int n = a.length;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int tmp = a[i][j];
                a[i][j] = a[j][i];
                a[j][i] = tmp;
            }
        }
    }

    private static void reverseRow(int[] row) {
        int l = 0, r = row.length - 1;
        while (l < r) {
            int tmp = row[l];
            row[l] = row[r];
            row[r] = tmp;
            l++;
            r--;
        }
    }

    private static void reverseCol(int[][] a, int col) {
        int top = 0;
        int bottom = a.length - 1;

        while (top < bottom) {
            int tmp = a[top][col];
            a[top][col] = a[bottom][col];
            a[bottom][col] = tmp;
            top++;
            bottom--;
        }
    }

    public static void rotate90AntiClockwise(int[][] a) {
        int n = a.length;
        if (n == 0 || a[0].length != n)
            return;

        transpose(a);

        for (int j = 0; j < n; j++) {
            reverseCol(a, j);
        }
    }

    public static void rotate90Clockwise(int[][] a) {
        int n = a.length;
        if (n == 0 || a[0].length != n)
            return;

        transpose(a);

        for (int i = 0; i < n; i++) {
            reverseRow(a[i]);
        }
    }
}
