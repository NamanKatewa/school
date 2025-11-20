#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <vector>

class Array {
private:
    int *data;
    int capacity;
    int size;

public:
    Array(int capacity);
    ~Array();

    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;
    bool isFull() const;

    void input(int n);
    void display() const;

    int getAt(int index) const;
    void setAt(int index, int value);

    void append(int value);
    void insertAt(int index, int value);
    void insertFront(int value);
    void insertBack(int value);

    int searchFirst(int key) const;
    std::vector<int> searchAll(int key) const;
    int countOccurrences(int key) const;

    void deleteAt(int index);
    bool deleteFirstByValue(int key);
    int deleteAllByValue(int key);

    int minElement() const;
    int maxElement() const;
    long long sum() const;
    double average() const;

    void reverse();
    void rotateLeft(int k);
    void rotateRight(int k);
};

#endif
