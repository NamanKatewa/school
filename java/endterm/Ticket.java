public class Ticket {

    static class SeatNotAvailableException extends Exception {
        public SeatNotAvailableException(String msg) {
            super(msg);
        }
    }

    static class TicketCounter {
        private int seats;

        public TicketCounter(int availbleSeats) {
            this.seats = availbleSeats;
        }

        public synchronized void bookSeats(String customer, int numOfseats) throws SeatNotAvailableException {
            if (numOfseats <= 0) {
                throw new SeatNotAvailableException("Invalid number of seats");
            }

            if (numOfseats > seats) {
                throw new SeatNotAvailableException("Not enough seats");
            }

            seats -= numOfseats;
        }
    }

    public static void main(String[] args) {
        TicketCounter counter = new TicketCounter(5);

        Runnable user1 = () -> {
            try {
                counter.bookSeats(Thread.currentThread().getName(), 3);
            } catch (SeatNotAvailableException e) {
                System.out.println(e.getMessage());
            }
        };

        Runnable user2 = () -> {
            try {
                counter.bookSeats(Thread.currentThread().getName(), 4);
            } catch (SeatNotAvailableException e) {
                System.out.println(e.getMessage());
            }
        };

        Thread t1 = new Thread(user1);
        Thread t2 = new Thread(user2);

        t1.start();
        t2.start();
    }
}
