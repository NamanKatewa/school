public class Interface {
    interface Payment {
        void pay(int amount);
    }

    class UpiPayment implements Payment {
        @Override
        public void pay(int amount) {
            System.out.println("Paid");
        }
    }

}
