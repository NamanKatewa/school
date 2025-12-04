import java.util.ArrayDeque;

public class RevStack {
    public static String reverseString(String s) {
        ArrayDeque<Character> st = new ArrayDeque<>();

        for (int i = 0; i < s.length(); i++) {
            st.push(s.charAt(i));
        }

        StringBuilder res = new StringBuilder();

        while (!st.isEmpty()) {
            res.append(st.pop());
        }
        return res.toString();
    }

    public static void reverseArray(int[] arr) {
        ArrayDeque<Integer> st = new ArrayDeque<>();

        for (int i = 0; i < arr.length; i++) {
            st.push(arr[i]);
        }

        int i = 0;
        while (!st.isEmpty()) {
            arr[i++] = st.pop();
        }
        ;
    }
}
