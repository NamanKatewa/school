import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Reader {

    public static void main(String[] args) {
        try {
            BufferedReader br = new BufferedReader(new FileReader("data.txt"));
            String line;

            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
