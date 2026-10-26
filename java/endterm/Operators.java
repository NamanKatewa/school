public class Operators {

    public static void main(String[] args) {
        int a = 10;
        int b = 3;
        boolean x = true;
        boolean y = false;
        int c = 5;
        int n = 4;
        int p = 5;
        int q = 3;

        // ARITHMETIC
        System.out.println(a + b);
        System.out.println(a - b);
        System.out.println(a * b);
        System.out.println(a / b);
        System.out.println(a % b);

        // RELATIONAL
        System.out.println(a > b);
        System.out.println(a < b);
        System.out.println(a >= b);
        System.out.println(a <= b);
        System.out.println(a == b);
        System.out.println(a != b);

        // LOGICAL
        System.out.println(x && y);
        System.out.println(x || y);
        System.out.println(!x);

        // ASSIGNMENT
        System.out.println(c = 3);
        System.out.println(c += 3);
        System.out.println(c -= 3);
        System.out.println(c *= 3);
        System.out.println(c /= 3);
        System.out.println(c %= 3);

        // UNARY
        System.out.println(n++);
        System.out.println(++n);
        System.out.println(n--);
        System.out.println(--n);

        // BITWISE
        System.out.println(p & q);
        System.out.println(p | q);
        System.out.println(p ^ q);
        System.out.println(~q);
        System.out.println(p << q);
        System.out.println(p >> q);
        System.out.println(p >>> q);

        // TERNARY
        int max = (a > b) ? a : b;

    }
}
