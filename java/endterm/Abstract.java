public class Abstract {
    abstract class Employee {
        private String name;

        Employee(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }

        abstract double calculateSalary();
    }

    class Manager extends Employee {
        private double base;
        private double bonus;

        Manager(String name, double baseSalary, double bonus) {
            super(name);
            this.base = baseSalary;
            this.bonus = bonus;
        }

        @Override
        double calculateSalary() {
            return base + bonus;
        }
    }

    class Developer extends Employee {
        private double rate;
        private int hours;

        Developer(String name, double hourlyRate, int hours) {
            super(name);
            this.rate = hourlyRate;
            this.hours = hours;
        }

        @Override
        double calculateSalary() {
            return rate * hours;
        }
    }

}
