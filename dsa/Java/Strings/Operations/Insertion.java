public class Insertion {

    public static void insertAtIndex(StringBuilder str, int pos, char txt) {
        str.insert(pos, txt);
    }

    public static void main(String[] args) {
        StringBuilder str = new StringBuilder("Hello");
        insertAtIndex(str, 1, 'c');
        System.out.println(str);
    }
}
