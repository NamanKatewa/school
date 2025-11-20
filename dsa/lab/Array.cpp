#include "Array.hpp"
#include <stdexcept>
#include <iostream>

Array::Array(int capacity) : capacity(capacity), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity must be a positive integer.");
    }
    data = new int[capacity];
}

Array::~Array() {
    delete[] data;
}

int Array::getSize() const {
    return size;
}

int Array::getCapacity() const {
    return capacity;
}

bool Array::isEmpty() const {
    return size == 0;
}

bool Array::isFull() const {
    return size == capacity;
}

void Array::input(int n) {
    if (n > capacity) {
        throw std::out_of_range("Input size exceeds capacity.");
    }
    size = n;
    for (int i = 0; i < size; ++i) {
        std::cin >> data[i];
    }
}

void Array::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

int Array::getAt(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

void Array::setAt(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    data[index] = value;
}

void Array::append(int value) {
    if (isFull()) {
        throw std::overflow_error("Array is full.");
    }
    data[size++] = value;
}

void Array::insertAt(int index, int value) {
    if (isFull()) {
        throw std::overflow_error("Array is full.");
    }
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range.");
    }
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void Array::insertFront(int value) {
    insertAt(0, value);
}

void Array::insertBack(int value) {
    append(value);
}

int Array::searchFirst(int key) const {
    for (int i = 0; i < size; ++i) {
        if (data[i] == key) {
            return i;
        }
    }
    return -1;
}

std::vector<int> Array::searchAll(int key) const {
    std::vector<int> indices;
    for (int i = 0; i < size; ++i) {
        if (data[i] == key) {
            indices.push_back(i);
        }
    }
    return indices;
}

int Array::countOccurrences(int key) const {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (data[i] == key) {
            count++;
        }
    }
    return count;
}

void Array::deleteAt(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range.");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

bool Array::deleteFirstByValue(int key) {
    int index = searchFirst(key);
    if (index != -1) {
        deleteAt(index);
        return true;
    }
    return false;
}

int Array::deleteAllByValue(int key) {
    int write_index = 0;
    int initial_size = size;
    for (int i = 0; i < size; ++i) {
        if (data[i] != key) {
            data[write_index++] = data[i];
        }
    }
    size = write_index;
    return initial_size - size;
}

int Array::minElement() const {
    if (isEmpty()) {
        throw std::logic_error("Array is empty.");
    }
    int min_val = data[0];
    for (int i = 1; i < size; ++i) {
        if (data[i] < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

int Array::maxElement() const {
    if (isEmpty()) {
        throw std::logic_error("Array is empty.");
    }
    int max_val = data[0];
    for (int i = 1; i < size; ++i) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

long long Array::sum() const {
    long long total = 0;
    for (int i = 0; i < size; ++i) {
        total += data[i];
    }
    return total;
}

double Array::average() const {
    if (isEmpty()) {
        throw std::logic_error("Array is empty.");
    }
    return static_cast<double>(sum()) / size;
}

void Array::reverse() {
    for (int i = 0; i < size / 2; ++i) {
        int temp = data[i];
        data[i] = data[size - 1 - i];
        data[size - 1 - i] = temp;
    }
}

void Array::rotateLeft(int k) {
    k %= size;
    if (k < 0) k += size;
    int* temp = new int[k];
    for (int i = 0; i < k; ++i) temp[i] = data[i];
    for (int i = 0; i < size - k; ++i) data[i] = data[i + k];
    for (int i = 0; i < k; ++i) data[size - k + i] = temp[i];
    delete[] temp;
}

void Array::rotateRight(int k) {
    k %= size;
    if (k < 0) k += size;
    int* temp = new int[k];
    for (int i = 0; i < k; ++i) temp[i] = data[size - k + i];
    for (int i = size - 1; i >= k; --i) data[i] = data[i - k];
    for (int i = 0; i < k; ++i) data[i] = temp[i];
    delete[] temp;
}
