public class DoublyLinkedList {

    Node head;
    Node tail;

    public DoublyLinkedList(int data) {
        this.head = new Node(data);
        this.tail = head;
    }

    class Node {
        int data;
        Node prev;
        Node next;

        public Node(int data) {
            this.data = data;
            this.next = null;
            this.prev = null;
        }
    }

    public void append(int data) {
        Node temp = this.head;

        while (temp.next != null) {
            temp = temp.next;
        }

        temp.next = new Node(data);
        temp.next.prev = temp;
        this.tail = temp.next;
    }

    public void insert(int data, int index) {
        Node temp = this.head;
        int count = 0;

        while (count != index - 1) {
            temp = temp.next;
            count++;
        }

        Node temp2 = temp.next;
        temp.next = new Node(data);
        temp.next.next = temp2;
        temp2.prev = temp.next;
        temp.next.prev = temp;

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
        temp.next.prev = temp;
        temp2 = null;
    }

    public void print() {
        Node temp = this.head;

        while (temp != null) {
            System.out.printf("%d <-> ", temp.data);
            temp = temp.next;
        }
        System.out.println();
    }

    public void printReverse() {
        Node temp = this.tail;

        while (temp != null) {
            System.out.printf("%d <-> ", temp.data);
            temp = temp.prev;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        DoublyLinkedList ll = new DoublyLinkedList(1);
        ll.append(2);
        ll.append(3);
        ll.append(4);
        ll.append(5);
        ll.insert(6, 2);
        ll.delete(2);
        ll.print();
        ll.printReverse();
    }
}
