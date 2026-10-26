import java.util.ArrayList;

public class Username {
    public static void main(String[] args) {
        ArrayList<String> usernames = new ArrayList<>();

        usernames.add("Naman");
        usernames.add("Sneha");
        usernames.add("Nikita");

        System.out.println(usernames);

        System.out.println(usernames.get(0));

        usernames.set(1, "CUTU");

        usernames.remove("Nikita");

    }
}
