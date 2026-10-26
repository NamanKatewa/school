import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class FileProg {
    public static void main(String[] args) {
        Path path = Path.of("data.txt");
        List<String> data = List.of("Naman", "Sneha", "Nikita", "Aditya", "Akansh");

        try {
            Files.write(path, data);
        } catch (IOException e) {
            System.out.println(e.getMessage());
            return;
        }

        ArrayList<String> employees;
        try {
            employees = new ArrayList<>(Files.readAllLines(path));
        } catch (IOException e) {
            System.out.println(e.getMessage());
            return;
        }

        Collections.sort(employees);

        for (String name : employees) {
            System.out.println(name);
        }
    }
}
