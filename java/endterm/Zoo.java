import java.util.ArrayList;

public class Zoo {

    abstract static class Animal {
        private String name;
        private int age;

        public Animal(String name, int age) {
            setName(name);
            setAge(age);
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            if (name == null || name.trim().isEmpty()) {
                throw new IllegalArgumentException("Name cannot be empty");
            }
            this.name = name;
        }

        public int getAge() {
            return age;
        }

        public void setAge(int age) {
            if (age < 0) {
                throw new IllegalArgumentException("Age cannot be negative");
            }
            this.age = age;
        }

        public void showInfo() {
            System.out.printf("%s -> Name: %s, Age: %d\n", getClass().getSimpleName(), name, age);
        }

        public abstract void makeSound();
    }

    static class Mammal extends Animal {
        public Mammal(String name, int age) {
            super(name, age);
        }

        @Override
        public void makeSound() {
            System.out.printf("%s (Mammal): Growl\n", getName());
        }
    }

    static class Bird extends Animal {
        public Bird(String name, int age) {
            super(name, age);
        }

        @Override
        public void makeSound() {
            System.out.printf("%s (Bird): Chirp\n", getName());
        }
    }

    static class Reptile extends Animal {
        public Reptile(String name, int age) {
            super(name, age);
        }

        @Override
        public void makeSound() {
            System.out.printf("%s (Mammal): Hiss\n", getName());
        }
    }

    static class ZooManagement {
        private final ArrayList<Animal> animals = new ArrayList<>();

        public void addAnimal(Animal a) {
            if (a == null) {
                throw new IllegalArgumentException("Animal cannot be null");
            }
            animals.add(a);
        }

        public void showAllAnimals() {
            for (Animal a : animals) {
                a.showInfo();
            }
        }

        public void makeAllSounds() {
            for (Animal a : animals) {
                a.makeSound();
            }
        }
    }

    public static void main(String[] args) {
        ZooManagement zoo = new ZooManagement();

        zoo.addAnimal(new Mammal("Tiger", 5));
        zoo.addAnimal(new Bird("Parrot", 2));
        zoo.addAnimal(new Reptile("Snake", 3));

        zoo.showAllAnimals();
        zoo.makeAllSounds();
    }

}
