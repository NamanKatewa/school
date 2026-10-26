class InheritanceTypes {

    // PARENT CLASS
    static class Animal {
        void eat() {
            System.out.println("Animal eats");
        }
    }

    // SINGLE INHERITANCE
    static class Bird extends Animal {
        void fly() {
            System.out.println("Bird flies");
        }
    }

    // HIERARCHIAL INHERITANCE
    static class Mammal extends Animal {
        void givesBirth() {
            System.out.println("Mammal gives birth");
        }
    }

    // MULTILEVEL INHERITANCE
    static class Dog extends Mammal {
        void bark() {
            System.out.println("Dog barks");
        }
    }
}