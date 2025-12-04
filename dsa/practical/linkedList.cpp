#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int d) : data(d), next(nullptr) {}
};

class SinglyLinkedList {
    Node *head;
public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        Node *cur = head;
        while (cur) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    void insertFront(int value) {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertBack(int value) {
        Node *newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node *cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
    }

    void insertAt(int pos, int value) {
        if (pos < 0) {
            cout << "Invalid position\n";
            return;
        }
        if (pos == 0) {
            insertFront(value);
            return;
        }
        Node *cur = head;
        for (int i = 0; cur && i < pos - 1; ++i) {
            cur = cur->next;
        }
        if (!cur) {
            cout << "Position out of bounds\n";
            return;
        }
        Node *newNode = new Node(value);
        newNode->next = cur->next;
        cur->next = newNode;
    }

    void deleteValue(int value) {
        if (!head) return;
        if (head->data == value) {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node *cur = head;
        while (cur->next && cur->next->data != value) {
            cur = cur->next;
        }
        if (cur->next) {
            Node *temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
        } else {
            cout << "Value not found\n";
        }
    }

    int search(int value) const {
        Node *cur = head;
        int index = 0;
        while (cur) {
            if (cur->data == value) {
                return index;
            }
            cur = cur->next;
            ++index;
        }
        return -1;
    }

    void display() const {
        Node *cur = head;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

int main() {
    SinglyLinkedList list;
    int choice, value, pos;

    while (true) {
        cout << "\n--- Singly Linked List Menu ---\n";
        cout << "1. Insert front\n";
        cout << "2. Insert back\n";
        cout << "3. Insert at position (0-based)\n";
        cout << "4. Delete value\n";
        cout << "5. Search value\n";
        cout << "6. Display list\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Value: ";
                cin >> value;
                list.insertFront(value);
                break;
            case 2:
                cout << "Value: ";
                cin >> value;
                list.insertBack(value);
                break;
            case 3:
                cout << "Position: ";
                cin >> pos;
                cout << "Value: ";
                cin >> value;
                list.insertAt(pos, value);
                break;
            case 4:
                cout << "Value to delete: ";
                cin >> value;
                list.deleteValue(value);
                break;
            case 5:
                cout << "Value to search: ";
                cin >> value;
                pos = list.search(value);
                if (pos == -1) cout << "Not found\n";
                else cout << "Found at index " << pos << "\n";
                break;
            case 6:
                cout << "List: ";
                list.display();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}