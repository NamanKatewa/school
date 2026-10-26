import java.io.File;

public class FilePerms {
    public static void main(String[] args) {
        File f = new File("data.txt");

        System.out.println("Before Changing Permissions");
        System.out.println(f.exists());
        System.out.println(f.canRead());
        System.out.println(f.canWrite());
        System.out.println(f.canExecute());
        System.out.println();

        f.setReadable(false);
        f.setWritable(false);
        f.setExecutable(false);

        System.out.println("After Changing Permissions");
        System.out.println(f.exists());
        System.out.println(f.canRead());
        System.out.println(f.canWrite());
        System.out.println(f.canExecute());
    }
}
