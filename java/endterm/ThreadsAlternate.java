public class ThreadsAlternate {
    static class Printer {
        private int n = 1;
        private final int max = 10;

        public synchronized void printOdd() {
            while (n <= max) {
                while (n % 2 == 0) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        System.out.println(e.getMessage());
                        return;
                    }
                }
                if (n <= max) {
                    System.out.println(n++);
                    notifyAll();
                }
            }
        }

        public synchronized void printEven() {
            while (n <= max) {
                while (n % 2 != 0) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        System.out.println(e.getMessage());
                        return;
                    }
                }
                if (n <= max) {
                    System.out.println(n++);
                    notifyAll();
                }
            }
        }

        public static void main(String[] args) {
            Printer p = new Printer();

            Thread t1 = new Thread(p::printOdd);
            Thread t2 = new Thread(p::printEven);

            t1.start();
            t2.start();
        }
    }
}
