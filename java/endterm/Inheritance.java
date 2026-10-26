public class Inheritance {

    static class Person {
        String name;
        int age;

        Person(String name, int age) {
            this.name = name;
            this.age = age;
        }

        void showPerson() {
            System.out.printf("Name: %s, Age: %d\n", name, age);
        }
    }

    static class Employee extends Person {
        int employeeId;

        Employee(String name, int age, int employeeId) {
            super(name, age);
            this.employeeId = employeeId;
        }

        void showEmployee() {
            showPerson();
            System.out.printf("Employee ID: %d\n", employeeId);
        }
    }

    public static void main(String[] args) {
        Person p = new Person("Naman", 21);
        Employee e = new Employee("Harsh", 35, 1001);

        p.showPerson();
        e.showEmployee();

    }

}
