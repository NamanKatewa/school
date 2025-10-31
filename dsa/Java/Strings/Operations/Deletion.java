public class Deletion {

    public static void deleteAtIndex(StringBuilder str, int pos) {
        str.deleteCharAt(pos);
    }

    public static void main(String[] args) {
        StringBuilder str = new StringBuilder("Hello");
        deleteAtIndex(str, 1);
        System.out.println(str);
    }

}
