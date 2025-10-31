import java.util.ArrayList;

public class Search {

    public static int searchFirstOccurence(String str, char s) {

        for (int i = 0; i < str.length(); i++) {
            if (s == str.charAt(i)) {
                return i;
            }
        }

        return 1;
    }

    public static ArrayList<Integer> searchAllOccurence(String str, char s) {
        ArrayList<Integer> result = new ArrayList<>();
        for (int i = 0; i < str.length(); i++) {
            if (s == str.charAt(i)) {
                result.add(i);
            }
        }
        return result;
    }

    public static void main(String[] args) {
        String str = "naman";
        ArrayList<Integer> result = searchAllOccurence(str, 'a');
        System.out.println(result);
    }
}