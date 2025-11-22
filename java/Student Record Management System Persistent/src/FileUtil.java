import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class FileUtil {

    private static final String FILE_NAME = "students.txt";

    public static List<Student> loadStudents() {
        List<Student> students = new ArrayList<>();
        File file = new File(FILE_NAME);

        if (!file.exists()) {
            System.out.println("Data file '" + FILE_NAME + "' not found. Starting with an empty list.");
            return students;
        }

        printFileAttributes(file);

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                Student s = Student.fromFileString(line);
                if (s != null) {
                    students.add(s);
                }
            }
        } catch (IOException e) {
            System.out.println("Error while reading students from file: " + e.getMessage());
        }

        demonstrateRandomAccess(file);

        return students;
    }

    public static void saveStudents(List<Student> students) {
        File file = new File(FILE_NAME);
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(file))) {
            for (Student s : students) {
                bw.write(s.toFileString());
                bw.newLine();
            }
            System.out.println("Students saved successfully to '" + FILE_NAME + "'.");
        } catch (IOException e) {
            System.out.println("Error while writing students to file: " + e.getMessage());
        }
    }

    private static void printFileAttributes(File file) {
        System.out.println("=== File Attributes ===");
        System.out.println("Absolute Path: " + file.getAbsolutePath());
        System.out.println("File Size: " + file.length() + " bytes");
        System.out.println("Last Modified: " + new Date(file.lastModified()));
        System.out.println("=======================");
    }

    private static void demonstrateRandomAccess(File file) {
        if (!file.exists() || file.length() == 0) {
            return;
        }
        System.out.println("=== RandomAccessFile Demo ===");
        try (RandomAccessFile raf = new RandomAccessFile(file, "r")) {
            raf.seek(0);
            String firstLine = raf.readLine();
            if (firstLine != null) {
                System.out.println("First record (raw line) using RandomAccessFile:");
                System.out.println(firstLine);
            } else {
                System.out.println("File is empty for RandomAccessFile demo.");
            }
        } catch (IOException e) {
            System.out.println("RandomAccessFile error: " + e.getMessage());
        }
        System.out.println("==============================");
    }
}
