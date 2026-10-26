public class ShapeClass {
    interface Shape {
        double perimeter();

        double area();
    }

    class Circle implements Shape {
        private double r;

        Circle(double radius) {
            this.r = radius;
        }

        @Override
        public double perimeter() {
            return 2 * (22 / 7) * r;
        }

        public double area() {
            return (22 / 7) * r * r;
        }
    }

    class Rectangle implements Shape {
        private double l;
        private double b;

        Rectangle(double length, double breadth) {
            this.l = length;
            this.b = breadth;
        }

        @Override
        public double perimeter() {
            return 2 * l * b;
        }

        @Override
        public double area() {
            return l * b;
        }
    }
}
