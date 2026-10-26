import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Copy {
    public static void main(String[] args) {
        String src = "input.jpeg";
        String dest = "output.jpeg";

        try {
            FileInputStream fin = new FileInputStream(src);
            FileOutputStream fout = new FileOutputStream(dest);

            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = fin.read(buffer)) != -1) {
                fout.write(buffer, 0, bytesRead);
            }
            fin.close();
            fout.close();
        } catch (IOException e) {
            System.out.println("Failed" + e.getMessage());
        }
    }
}
