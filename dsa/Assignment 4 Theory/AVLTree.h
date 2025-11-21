#ifndef AVLTREE_H
#define AVLTREE_H

#include "CityData.h"
#include <iostream>

class AVLTree {
    struct Node {
        CityNode data;
        Node *left, *right;
        int height;
    };
    Node* root;

    int height(Node* n);
    int getBalance(Node* n);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, CityNode data);
    Node* search(Node* node, int id);
    void inOrder(Node* root);


public:
    AVLTree() : root(nullptr) {}

    void insert(CityNode data);
    CityNode* search(int id);
    void inOrder();
};

#endif
