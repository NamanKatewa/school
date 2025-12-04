#include<vector>
#include<iostream>
#include<stdexcept>
using namespace std;

class PriorityQueue {
    vector<int> heap;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i)   const { return 2 * i + 1; }
    int right(int i)  const { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int n = static_cast<int>(heap.size());
        while (true) {
            int l = left(i);
            int r = right(i);
            int largest = i;

            if (l < n && heap[l] > heap[largest]) {
                largest = l;
            }
            if (r < n && heap[r] > heap[largest]) {
                largest = r;
            }

            if (largest != i) {
                swap(heap[i], heap[largest]);
                i = largest;
            } else {
                break;
            }
        }
    }

public:
    bool empty() const {
        return heap.empty();
    }

    int top() const {
        if (heap.empty()) {
            throw runtime_error("PriorityQueue is empty");
        }
        return heap[0];
    }

    void push(int value) {
        heap.push_back(value);
        heapifyUp(static_cast<int>(heap.size()) - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    void printInternal() const {
        for (int x : heap) {
            cout << x << " ";
        }
        cout << "\n";
    }
};

int main() {
    PriorityQueue pq;
    int choice, value;

    while (true) {
        cout << "\n--- Priority Queue (Max-Heap) Menu ---\n";
        cout << "1. Insert (push)\n";
        cout << "2. Remove max (pop)\n";
        cout << "3. Get max (top)\n";
        cout << "4. Display internal heap\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) return 0;

        try {
            switch (choice) {
                case 1:
                    cout << "Value: ";
                    cin >> value;
                    pq.push(value);
                    break;
                case 2:
                    pq.pop();
                    break;
                case 3:
                    cout << "Max element: " << pq.top() << "\n";
                    break;
                case 4:
                    cout << "Heap: ";
                    pq.printInternal();
                    break;
                case 5:
                    return 0;
                default:
                    cout << "Invalid choice\n";
            }
        } catch (const runtime_error &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}