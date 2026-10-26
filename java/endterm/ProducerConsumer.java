public class ProducerConsumer {
    static class Buffer {
        private int value;
        private boolean hasValue = false;

        private void log(String msg) {
            System.out.println(msg);
        }

        public synchronized void put(int v) throws InterruptedException {
            while (hasValue) {
                log("Buffer Full");
                wait();
            }

            value = v;
            hasValue = true;
            log("Produced " + v);
            notifyAll();
        }

        public synchronized int take() throws InterruptedException {
            while (!hasValue) {
                log("Buffer Empty");
                wait();
            }

            int v = value;
            hasValue = false;
            log("Consumed " + v);
            notifyAll();
            return v;
        }

    }

    static class Producer implements Runnable {
        private final Buffer buffer;
        private final int count;

        Producer(Buffer buffer, int count) {
            this.buffer = buffer;
            this.count = count;
        }

        @Override
        public void run() {
            try {
                for (int i = 0; i <= count; i++) {
                    buffer.put(i);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println(e.getMessage());
            }
        }
    }

    static class Consumer implements Runnable {
        private final Buffer buffer;
        private final int count;

        Consumer(Buffer buffer, int count) {
            this.buffer = buffer;
            this.count = count;
        }

        @Override
        public void run() {
            try {
                for (int i = 0; i <= count; i++) {
                    buffer.take();
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println(e.getMessage());
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Buffer buffer = new Buffer();
        int n = 10;

        Thread producer = new Thread(new Producer(buffer, n));
        Thread consumer = new Thread(new Consumer(buffer, n));

        producer.start();
        consumer.start();

        producer.join();
        consumer.join();
    }
}
