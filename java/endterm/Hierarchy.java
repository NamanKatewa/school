public class Hierarchy {
    abstract static class Vehicle {
        String brand;
        int maxSpeed;

        Vehicle(String brand, int maxSpeed) {
            this.brand = brand;
            this.maxSpeed = maxSpeed;
        }

        abstract void drive();
    }

    static class Car extends Vehicle {
        int numberOfDoors;

        Car(String brand, int maxSpeed, int numberOfDoors) {
            super(brand, maxSpeed);
            this.numberOfDoors = numberOfDoors;
        }

        @Override
        void drive() {
            System.out.printf("Driving a car: %s, Speed: %dkm/h, Doors: %d\n", brand, maxSpeed, numberOfDoors);
        }
    }

    static class Bike extends Vehicle {
        boolean hasCarrier;

        Bike(String brand, int maxSpeed, boolean hasCarrier) {
            super(brand, maxSpeed);
            this.hasCarrier = hasCarrier;
        }

        @Override
        void drive() {
            System.out.printf("Driving a car: %s, Speed: %dkm/h, Carrier: %b\n", brand, maxSpeed, hasCarrier);
        }
    }

    static class Truck extends Vehicle {
        int loadCapacity;

        Truck(String brand, int maxSpeed, int loadCapacity) {
            super(brand, maxSpeed);
            this.loadCapacity = loadCapacity;
        }

        @Override
        void drive() {
            System.out.printf("Driving a car: %s, Speed: %dkm/h, Load: %d\n", brand, maxSpeed, loadCapacity);
        }
    }

    public static void main(String[] args) {
        Car car = new Car("Honda", 180, 4);
        Bike bike = new Bike("Yamaha", 120, true);
        Truck truck = new Truck("Toyota", 100, 20);

        car.drive();
        bike.drive();
        truck.drive();
    }
}
