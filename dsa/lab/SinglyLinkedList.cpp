#include "SinglyLinkedList.hpp"
#include <stdexcept>
#include <iostream>

SinglyLinkedList::SinglyLinkedList() : head(nullptr), size(0) {}

SinglyLinkedList::~SinglyLinkedList() {
    clear();
}

int SinglyLinkedList::getSize() const {
    return size;
}

bool SinglyLinkedList::isEmpty() const {
    return head == nullptr;
}

void SinglyLinkedList::clear() {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

void SinglyLinkedList::display() const {
    ListNode *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int SinglyLinkedList::getAt(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    ListNode *current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

void SinglyLinkedList::setAt(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    ListNode *current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    current->data = value;
}

void SinglyLinkedList::insertFront(int value) {
    ListNode *newNode = new ListNode(value);
    newNode->next = head;
    head = newNode;
    size++;
}

void SinglyLinkedList::insertBack(int value) {
    ListNode *newNode = new ListNode(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        ListNode *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void SinglyLinkedList::insertAt(int index, int value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range.");
    }
    if (index == 0) {
        insertFront(value);
    } else {
        ListNode *newNode = new ListNode(value);
        ListNode *current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

void SinglyLinkedList::deleteFront() {
    if (isEmpty()) {
        throw std::logic_error("List is empty.");
    }
    ListNode *temp = head;
    head = head->next;
    delete temp;
    size--;
}

void SinglyLinkedList::deleteBack() {
    if (isEmpty()) {
        throw std::logic_error("List is empty.");
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        ListNode *current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}

void SinglyLinkedList::deleteAt(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    if (index == 0) {
        deleteFront();
    } else {
        ListNode *current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        ListNode *temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
    }
}

int SinglyLinkedList::searchFirst(int key) const {
    ListNode *current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == key) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

std::vector<int> SinglyLinkedList::searchAll(int key) const {
    std::vector<int> indices;
    ListNode *current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == key) {
            indices.push_back(index);
        }
        current = current->next;
        index++;
    }
    return indices;
}

int SinglyLinkedList::countOccurrences(int key) const {
    int count = 0;
    ListNode *current = head;
    while (current != nullptr) {
        if (current->data == key) {
            count++;
        }
        current = current->next;
    }
    return count;
}

bool SinglyLinkedList::deleteFirstByValue(int key) {
    int index = searchFirst(key);
    if (index != -1) {
        deleteAt(index);
        return true;
    }
    return false;
}

int SinglyLinkedList::deleteAllByValue(int key) {
    int deletedCount = 0;
    ListNode *current = head;
    ListNode *prev = nullptr;

    while (current != nullptr) {
        if (current->data == key) {
            if (prev == nullptr) {
                head = current->next;
                delete current;
                current = head;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
            size--;
            deletedCount++;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return deletedCount;
}

void SinglyLinkedList::reverse() {
    ListNode *prev = nullptr;
    ListNode *current = head;
    ListNode *next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void SinglyLinkedList::concatenate(SinglyLinkedList &other) {
    if (other.isEmpty()) {
        return;
    }
    if (isEmpty()) {
        head = other.head;
    } else {
        ListNode *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = other.head;
    }
    size += other.size;
    other.head = nullptr;
    other.size = 0;
}
