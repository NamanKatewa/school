import java.util.ArrayDeque;

public class Brackets {
    private static boolean isPair(char open, char close) {
        if (open == '(' && close == ')') {
            return true;
        }
        if (open == '{' && close == '}') {
            return true;
        }
        if (open == '[' && close == ']') {
            return true;
        }
        return false;
    }

    public static boolean isBalanced(String s) {
        ArrayDeque<Character> st = new ArrayDeque<>();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else {
                if (st.isEmpty()) {
                    return false;
                }
                if (isPair(st.pop(), c)) {
                    continue;
                }
                return false;
            }

        }
        if (st.isEmpty()) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        boolean res = isBalanced("[{()}({[]})(([]){({[]})[()()]}){{[()()]({[]})}}]");
        System.out.println(res);
    }

}
