public class Length {

    public static int lengthOfString(String str) {
        int count = 0;
        for (char _ : str.toCharArray()) {
            count++;
        }
        return count;
    }

    public static void main(String[] args) {
        String str = "Hello";
        int result = lengthOfString(str);
        System.out.println(result);
    }
}
