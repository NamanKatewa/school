public class Substring {

    public static int checkSubstring(String str, String sub) {

        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == sub.charAt(0)) {
                int j;
                for (j = 0; j < sub.length(); j++) {
                    if (sub.charAt(j) != str.charAt(i + j)) {
                        break;
                    }
                }
                if (j == sub.length()) {
                    return i;
                }
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        String str = "geeksforgeeks";
        String sub = "eks";
        int result = checkSubstring(str, sub);
        System.out.println(result);
    }
}
