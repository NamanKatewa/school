public class InterfacePoly {
    interface Pay {
        void pay();
    }

    static class Upi implements Pay {
        public void pay() {
            System.out.println("Paying via UPI");
        }
    }

    static class Card implements Pay {
        public void pay() {
            System.out.println("Paying via Card");
        }
    }

    public class Main {
        public static void main(String[] args) {
            Pay p = new Upi();
            p.pay();

            p = new Card();
            p.pay();
        }
    }

}
