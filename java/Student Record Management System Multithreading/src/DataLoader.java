public class DataLoader implements Runnable {

    @Override
    public void run() {
        System.out.printf(Constants.ANSI_PURPLE + "Loading..." + Constants.ANSI_RESET);
        for (int i = 0; i < 10; i++) {
            try {
                Thread.sleep(200);
                System.out.printf(Constants.ANSI_PURPLE + "." + Constants.ANSI_RESET);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println();
    }
}
