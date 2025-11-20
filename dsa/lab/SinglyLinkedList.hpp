#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <vector>
#include <iostream>

struct ListNode {
    int data;
    ListNode *next;

    ListNode(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    ListNode *head;
    int size;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    int getSize() const;
    bool isEmpty() const;
    void clear();
    void display() const;

    int getAt(int index) const;
    void setAt(int index, int value);

    void insertFront(int value);
    void insertBack(int value);
    void insertAt(int index, int value);

    void deleteFront();
    void deleteBack();
    void deleteAt(int index);

    int searchFirst(int key) const;
    std::vector<int> searchAll(int key) const;
    int countOccurrences(int key) const;

    bool deleteFirstByValue(int key);
    int deleteAllByValue(int key);

    void reverse();
    void concatenate(SinglyLinkedList &other);
};

#endif
