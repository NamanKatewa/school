#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Array.hpp"
#include "SinglyLinkedList.hpp"
#include "StackArray.hpp"
#include "StackList.hpp"
#include "QueueArray.hpp"
#include "QueueList.hpp"
#include "PostfixEvaluator.hpp"
#include "SearchAlgorithms.hpp"
#include "SortingAlgorithms.hpp"
#include "BinarySearchTree.hpp"
#include "ComplexityDemo.hpp"

void printVector(const std::vector<int>& vec) {
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void lab1() {
    std::cout << "\n\n--- Lab 1: Arrays ---" << std::endl;
    try {
        Array arr(10);
        std::cout << "\nAppending Elements" << std::endl;
        arr.append(10);
        arr.append(20);
        arr.append(30);
        arr.append(40);
        arr.append(50);
        arr.append(50);
        arr.append(10);
        arr.append(60);
        arr.append(10);
        arr.display();
        std::cout << "\nInserting at Start" << std::endl;
        arr.insertFront(5);
        arr.display();
        std::cout << "\nGet Element at Index" << std::endl;
        int res = arr.getAt(2);
        std::cout << res << std::endl;
        std::cout << "\nSet Element at Index" << std::endl;
        arr.setAt(5, 45);
        arr.display();
        std::cout << "\nSearching First Occurence" << std::endl;
        arr.display();
        res = arr.searchFirst(10);
        std::cout << res << std::endl;
        std::cout << "\nSearching All Occurences" << std::endl;
        arr.display();
        std::vector<int> result = arr.searchAll(10);
        printVector(result);
        std::cout << "\nCount Occurences" << std::endl;
        res = arr.countOccurrences(10);
        std::cout << res << std::endl;
        std::cout << "\nMin: " << arr.minElement() << ", Max: " << arr.maxElement() << std::endl;
        std::cout << "\nSum of All Elements" << std::endl;
        long long result1 = arr.sum();
        std::cout << result1 << std::endl;
        std::cout << "\nAverage of All Elements" << std::endl;
        double result2 = arr.average();
        std::cout << result2 << std::endl;
        std::cout << "\nReversing Array" << std::endl;
        arr.display();
        arr.reverse();
        arr.display();
        std::cout << "\nRotate Left" << std::endl;
        arr.reverse();
        arr.display();
        arr.rotateLeft(2);
        arr.display();
        arr.rotateRight(2);
        std::cout << "\nRotate Right" << std::endl;
        arr.display();
        arr.rotateRight(2);
        arr.display();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in Lab 1: " << e.what() << std::endl;
    }
}

void lab2() {
    std::cout << "\n\n--- Lab 2: ComplexityDemo ---" << std::endl;
    try {
        ComplexityDemo::runAllDemos();
    } catch (const std::exception& e) {
        std::cerr << "Error in Lab 2: " << e.what() << std::endl;
    }
}

void lab3() {
    std::cout << "\n--- Lab 3: SinglyLinkedList ---" << std::endl;
    try {
        SinglyLinkedList list;
        std::cout << "\nInserting at the Back" << std::endl;
        list.insertBack(10);
        list.insertBack(20);
        list.insertBack(30);
        list.display();
        std::cout << "\nInserting at the Front" << std::endl;
        list.insertFront(5);
        list.insertFront(20);
        list.display();
        std::cout << "\nReversing the List" << std::endl;
        list.reverse();
        list.display();
        std::cout << "\nSearching All Occurences" << std::endl;
        list.reverse();
        std::vector<int> res = list.searchAll(20);
        printVector(res);
        std::cout << "\nConcatenating another Linked List" << std::endl;
        SinglyLinkedList list2;
        list2.insertBack(60);
        list2.insertBack(70);
        list2.insertBack(80);
        std::cout << "List One:";
        list.display();
        std::cout << "List Two:";
        list2.display();
        list.concatenate(list2);
        std::cout << std::endl;
        list.display();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in Lab 3: " << e.what() << std::endl;
    }
}

void lab4() {
    std::cout << "\n--- Lab 4: Stacks and Queues ---" << std::endl;
    try {
        std::cout << "\nStackArray" << std::endl;
        StackArray sa(5);
        sa.push(1); sa.push(2);
        sa.push(3);
        sa.push(4);
        sa.display();
        std::cout << "StackArray Popped: " << sa.pop() << std::endl;
        sa.display();

        std::cout << "\nStackList" << std::endl;
        StackList sl;
        sl.push(3); sl.push(4);
        sl.push(5);
        sl.push(6);
        sl.display();
        std::cout << "StackList Popped: " << sl.pop() << std::endl;
        sl.display();

        std::cout << "\nQueueArray" << std::endl;
        QueueArray qa(5);
        qa.enqueue(5); qa.enqueue(6);
        qa.enqueue(7);
        qa.enqueue(8);
        qa.display();
        std::cout << "QueueArray Dequeued: " << qa.dequeue() << std::endl;
        qa.display();

        std::cout << "\nQueueList" << std::endl;
        QueueList ql;
        ql.enqueue(7); ql.enqueue(8);
        ql.enqueue(9);
        ql.enqueue(10);
        ql.display();
        std::cout << "QueueList Dequeued: " << ql.dequeue() << std::endl;
        ql.display();

    } catch (const std::exception& e) {
        std::cerr << "Error in Lab 4: " << e.what() << std::endl;
    }
}

void lab5() {
    std::cout << "\n--- Lab 5: Postfix Evaluator ---" << std::endl;
    try {
        std::cout << "Result of \"5 1 2 + 4 * + 3 -\": " << PostfixEvaluator::evaluate("5 1 2 + 4 * + 3 -") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in Lab 5: " << e.what() << std::endl;
    }
}

void lab6() {
    std::cout << "\n--- Lab 6: Search Algorithms ---" << std::endl;
    try {
        std::vector<int> sorted_arr = {1, 2, 2, 2, 5, 7, 8, 9};
        long long comparisons = 0;
        int index = SearchAlgorithms::binarySearchIterative(sorted_arr, 5, comparisons);
        std::cout << "Binary Search for 5: index " << index << " (Comparisons: " << comparisons << ")" << std::endl;
        index = SearchAlgorithms::binarySearchRecursive(sorted_arr, 2, comparisons);
        std::cout << "Binary Search Recursive for 2: index " << index << " (Comparisons: " << comparisons << ")" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in Lab 6: " << e.what() << std::endl;
    }
}

void lab7() {
    std::cout << "\n--- Lab 7: Sorting Algorithms ---" << std::endl;
    try {
        std::vector<int> data = {5, 2, 8, 2, 9, 1, 7, 4};
        long long comparisons = 0, moves = 0;

        std::cout << "Original array: ";
        printVector(data);

        std::vector<int> bubble_data = data;
        comparisons = 0; moves = 0;
        SortingAlgorithms::bubbleSort(bubble_data, true, comparisons, moves);
        std::cout << "\nBubble Sorted (ascending): ";
        printVector(bubble_data);
        SortingAlgorithms::printStats("Bubble Sort (ascending)", bubble_data.size(), comparisons, moves);

        bubble_data = data;
        comparisons = 0; moves = 0;
        SortingAlgorithms::bubbleSort(bubble_data, false, comparisons, moves);
        std::cout << "Bubble Sorted (descending): ";
        printVector(bubble_data);
        SortingAlgorithms::printStats("Bubble Sort (descending)", bubble_data.size(), comparisons, moves);

        std::vector<int> selection_data = data;
        comparisons = 0; moves = 0;
        SortingAlgorithms::selectionSort(selection_data, true, comparisons, moves);
        std::cout << "\nSelection Sorted (ascending): ";
        printVector(selection_data);
        SortingAlgorithms::printStats("Selection Sort (ascending)", selection_data.size(), comparisons, moves);
        
        selection_data = data;
        comparisons = 0; moves = 0;
        SortingAlgorithms::selectionSort(selection_data, false, comparisons, moves);
        std::cout << "Selection Sorted (descending): ";
        printVector(selection_data);
        SortingAlgorithms::printStats("Selection Sort (descending)", selection_data.size(), comparisons, moves);

        std::vector<int> insertion_data = data;
        comparisons = 0; moves = 0;
        SortingAlgorithms::insertionSort(insertion_data, true, comparisons, moves);
        std::cout << "\nInsertion Sorted (ascending): ";
        printVector(insertion_data);
        SortingAlgorithms::printStats("Insertion Sort (ascending)", insertion_data.size(), comparisons, moves);

        insertion_data = data;
        comparisons = 0; moves = 0;
        SortingAlgorithms::insertionSort(insertion_data, false, comparisons, moves);
        std::cout << "Insertion Sorted (descending): ";
        printVector(insertion_data);
        SortingAlgorithms::printStats("Insertion Sort (descending)", insertion_data.size(), comparisons, moves);

    } catch (const std::exception& e) {
        std::cerr << "Error in Lab 7: " << e.what() << std::endl;
    }
}

void lab8() {
    std::cout << "\n--- Lab 8: Binary Search Tree ---" << std::endl;
    try {
        BinarySearchTree bst;
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        std::cout << "Inorder traversal: ";
        bst.inorder();
        std::cout << std::endl;

        std::cout << "Preorder traversal: ";
        bst.preorder();
        std::cout << std::endl;

        std::cout << "Postorder traversal: ";
        bst.postorder();
        std::cout << std::endl;

        std::cout << "Level order traversal: ";
        bst.levelOrder();
        std::cout << std::endl;

        std::cout << "Search for 40: " << (bst.search(40) ? "Found" : "Not Found") << std::endl;
        std::cout << "Search for 90: " << (bst.search(90) ? "Found" : "Not Found") << std::endl;

        std::cout << "Height: " << bst.height() << std::endl;
        std::cout << "Number of nodes: " << bst.countNodes() << std::endl;
        std::cout << "Number of leaves: " << bst.countLeaves() << std::endl;
        std::cout << "Number of internal nodes: " << bst.countInternalNodes() << std::endl;
        
        std::cout << "Min value: " << bst.minValue() << std::endl;
        std::cout << "Max value: " << bst.maxValue() << std::endl;

        std::cout << "\nMirroring the tree..." << std::endl;
        bst.mirror();

        std::cout << "Inorder traversal after mirror: ";
        bst.inorder();
        std::cout << std::endl;
        
        std::cout << "Level order traversal after mirror: ";
        bst.levelOrder();
        std::cout << std::endl;

        std::cout << "\nClearing the tree..." << std::endl;
        bst.clear();
        std::cout << "Number of nodes after clear: " << bst.countNodes() << std::endl;
        std::cout << "Inorder traversal after clear: ";
        bst.inorder();
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error in Lab 8: " << e.what() << std::endl;
    }
}


int main() {
    lab1();
    lab2();
    lab3();
    lab4();
    lab5();
    lab6();
    lab7();
    lab8();

    return 0;
}