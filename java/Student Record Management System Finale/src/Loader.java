public class Loader implements Runnable {

    private final String message;
    private final int steps;
    private final long delayMillis;

    public Loader(String message) {
        this(message, 5, 250);
    }

    public Loader(String message, int steps, long delayMillis) {
        this.message = message;
        this.steps = steps;
        this.delayMillis = delayMillis;
    }

    @Override
    public void run() {
        System.out.print(ConsoleColors.BLUE_BOLD + message + ConsoleColors.RESET);
        for (int i = 0; i < steps; i++) {
            try {
                Thread.sleep(delayMillis);
            } catch (InterruptedException e) {
                // Ignore interruption for this simple loader
            }
            System.out.print(ConsoleColors.BLUE_BOLD + "." + ConsoleColors.RESET);
        }
        System.out.println();
    }
}
