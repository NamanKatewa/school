public class InterfaceInheritance {
    interface Playable {
        void play();
    }

    class Guitar implements Playable {
        @Override
        public void play() {
            System.out.println("Guitar");
        }
    }

    class Piano implements Playable {
        @Override
        public void play() {
            System.out.println("Piano");
        }
    }

}
