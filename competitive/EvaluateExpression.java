import java.util.ArrayDeque;
import java.util.Deque;

public class EvaluateExpression {
    private static boolean isOperator(String t) {
        return t.equals("+") || t.equals("-") || t.equals("*") ||
                t.equals("/") || t.equals("%") || t.equals("^");
    }

    private static int doOperation(int a, int b, String op) {
        switch (op) {
            case "+":
                return a + b;
            case "-":
                return a - b;
            case "*":
                return a * b;
            case "/":
                return a / b;
            case "%":
                return a % b;
            case "^":
                return (int) Math.pow(a, b);
            default:
                throw new RuntimeException("Bad Operation");
        }
    }

    public static int evaluatePostfix(String exp) {
        Deque<Integer> st = new ArrayDeque<>();
        String[] tokens = exp.trim().split("\\s+");

        for (String t : tokens) {
            if (t.isEmpty()) {
                continue;
            }

            if (!isOperator(t)) {
                int val = Integer.parseInt(t);
                st.push(val);
            } else {
                int b = st.pop();
                int a = st.pop();
                int res = doOperation(a, b, t);
                st.push(res);
            }
        }

        return st.pop();
    }
}
