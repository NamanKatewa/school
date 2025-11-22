import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class FileUtil {

    private static final String FILE_NAME = "students.txt";

    public static List<Student> loadStudents() {
        List<Student> students = new ArrayList<>();
        File file = new File(FILE_NAME);

        if (!file.exists()) {
            System.out.println(ConsoleColors.error("Data file 'students.txt' not found. Starting with an empty list."));
            return students;
        }

        System.out.println(ConsoleColors.header("Loading students from file '" + file.getAbsolutePath() + "'"));

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                Student s = Student.fromFileString(line);
                if (s != null) {
                    students.add(s);
                }
            }
        } catch (IOException e) {
            System.out.println(ConsoleColors.error("Error while reading students from file: " + e.getMessage()));
        }

        return students;
    }

    public static void saveStudents(List<Student> students) {
        File file = new File(FILE_NAME);

        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file))) {
            for (Student s : students) {
                bw.write(s.toFileString());
                bw.newLine();
            }
            System.out.println(ConsoleColors.success("Students saved successfully to '" + FILE_NAME + "'."));
        } catch (IOException e) {
            System.out.println(ConsoleColors.error("Error while writing students to file: " + e.getMessage()));
        }
    }
}
