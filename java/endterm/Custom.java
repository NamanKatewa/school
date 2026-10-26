public class Custom {
    public static void main(String[] args) {
        try {
            setAge(-5);
        } catch (NegativeAgeException e) {
            System.out.println(e.getMessage());
        }
    }

    static void setAge(int age) throws NegativeAgeException {
        if (age < 0) {
            throw new NegativeAgeException("Age cannot be negative");
        }
    }

    static class NegativeAgeException extends Exception {
        NegativeAgeException(String msg) {
            super(msg);
        }
    }
}
