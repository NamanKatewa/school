public class StringsCompare {
    public static void main(String[] args) {
        String str1 = "hello";
        String str2 = new String("hello");

        System.out.println(str1 == str2);
        System.out.println(str1.equals(str2));
    }

}
