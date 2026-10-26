public class Animal {
    void sound() {
        System.out.println("Sound");
    }
}

class Dog extends Animal {
    @Override
    void sound() {
        System.out.println("Bark");
    }
}