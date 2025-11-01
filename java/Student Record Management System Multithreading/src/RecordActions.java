public interface RecordActions {
    void addStudent();

    void deleteStudent() throws StudentNotFoundException;

    void updateStudent() throws StudentNotFoundException;

    void searchStudent() throws StudentNotFoundException;

    void viewAllStudents();

    void sortStudents();
}