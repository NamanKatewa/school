import java.util.ArrayDeque;
import java.util.Deque;

class InfixConverter {
    private static int precedence(char op) {
        switch (op) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
            case '%':
                return 2;
            case '^':
                return 3;
            default:
                return -1;
        }
    }

    private static boolean isRightAssociative(char op) {
        return op == '^';
    }

    private static boolean isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
    }

    public static String infixToPostfix(String infix) {
        StringBuilder res = new StringBuilder();
        Deque<Character> st = new ArrayDeque<>();

        for (int i = 0; i < infix.length(); i++) {
            char ch = infix.charAt(i);

            if (Character.isWhitespace(ch)) {
                continue;
            }

            if (Character.isLetterOrDigit(ch)) {
                res.append(ch);
            } else if (ch == '(') {
                st.push(ch);
            } else if (ch == ')') {
                while (!st.isEmpty() && st.peek() != '(') {
                    res.append(st.pop());
                }
                if (!st.isEmpty() && st.peek() == '(') {
                    st.pop();
                } else {
                    System.out.println("Invalid Expression");
                    return "";
                }
            } else if (isOperator(ch)) {

                while (!st.isEmpty() && isOperator(st.peek())) {
                    char topOp = st.peek();
                    int pTop = precedence(topOp);
                    int pCur = precedence(ch);

                    boolean shouldPop = (pTop > pCur) || (pTop == pCur && !isRightAssociative(ch));

                    if (shouldPop) {
                        res.append(st.pop());
                    } else {
                        break;
                    }
                }
                st.push(ch);
            } else {
                System.out.println("Unkown Symbol: " + ch);
                return "";
            }
        }

        while (!st.isEmpty()) {
            char top = st.pop();
            if (top == '(' || top == ')') {
                System.out.println("Invalid Expression");
                return "";
            }
            res.append(top);
        }

        return res.toString();
    }

    public static String infixToPrefix(String infix) {

        StringBuilder reversed = new StringBuilder();

        for (int i = 0; i < infix.length(); i++) {
            if (infix.charAt(i) == ')') {
                reversed.append('(');
            } else if (infix.charAt(i) == '(') {
                reversed.append(')');
            } else {
                reversed.append(infix.charAt(i));
            }
        }

        String result = infixToPostfix(reversed.toString());

        StringBuilder res = new StringBuilder(result);

        return res.reverse().toString();
    }

}