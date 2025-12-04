import java.util.ArrayDeque;
import java.util.NoSuchElementException;

public class QueueStack<T> {
    private ArrayDeque<T> in;
    private ArrayDeque<T> out;

    public QueueStack() {
        in = new ArrayDeque<>();
        out = new ArrayDeque<>();
    }

    public void enqueue(T x) {
        in.push(x);
    }

    private void shiftStacks() {
        if (out.isEmpty()) {
            while (!in.isEmpty()) {
                out.push(in.pop());
            }
        }
    }

    public T dequeue() {
        shiftStacks();
        if (out.isEmpty()) {
            throw new NoSuchElementException("empty");
        }
        return out.pop();
    }
}
