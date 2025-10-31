
public class SinglyLinkedList {
    Node head;

    public SinglyLinkedList(int data) {
        this.head = new Node(data);
    }

    class Node {

        int data;
        Node next;

        public Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    public void append(int data) {
        Node temp = this.head;

        while (temp.next != null) {
            temp = temp.next;
        }
        temp.next = new Node(data);
    }

    public void print() {
        Node temp = this.head;

        while (temp != null) {
            System.out.printf("%d -> ", temp.data);
            temp = temp.next;
        }
    }

    public void insert(int index, int data) {
        Node temp = this.head;
        int count = 0;
        while (count != index - 1) {
            temp = temp.next;
            count++;
        }

        Node temp2 = temp.next;
        temp.next = new Node(data);
        temp.next.next = temp2;

    }

    public void delete(int index) {
        Node temp = this.head;

        int count = 0;

        while (count != index - 1) {
            temp = temp.next;
            count++;
        }

        Node temp2 = temp.next;
        temp.next = temp.next.next;

        temp2.next = null;
    }

    public int search(int item) {
        Node temp = this.head;
        int count = 0;

        while (temp != null) {
            if (temp.data == item) {
                return count;
            }
            temp = temp.next;
            count++;
        }

        return -1;
    }

    public void reverse() {

        Node prev = null;
        Node current = this.head;
        Node next = current.next;

        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }

        this.head = prev;

    }

    public static void main(String[] args) {
        SinglyLinkedList ll = new SinglyLinkedList(1);
        ll.append(2);
        ll.append(3);
        ll.append(4);

        ll.insert(2, 5);

        ll.delete(2);

        ll.reverse();
        ll.print();
    }
}
