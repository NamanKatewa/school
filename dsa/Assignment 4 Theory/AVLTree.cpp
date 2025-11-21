#include "AVLTree.h"
#include <algorithm>
#include <iostream>

int AVLTree::height(Node* n) {
    return n == nullptr ? 0 : n->height;
}

int AVLTree::getBalance(Node* n) {
    return n == nullptr ? 0 : height(n->left) - height(n->right);
}

AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLTree::Node* AVLTree::insert(Node* node, CityNode data) {
    if (node == nullptr) {
        Node* temp = new Node();
        temp->data = data;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->height = 1;
        return temp;
    }

    if (data.id < node->data.id) {
        node->left = insert(node->left, data);
    } else if (data.id > node->data.id) {
        node->right = insert(node->right, data);
    } else {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data.id < node->left->data.id) {
        return rightRotate(node);
    }

    if (balance < -1 && data.id > node->right->data.id) {
        return leftRotate(node);
    }

    if (balance > 1 && data.id > node->left->data.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.id < node->right->data.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(CityNode data) {
    root = insert(root, data);
}

AVLTree::Node* AVLTree::search(Node* node, int id) {
    if (node == nullptr || node->data.id == id) {
        return node;
    }

    if (id < node->data.id) {
        return search(node->left, id);
    }

    return search(node->right, id);
}

CityNode* AVLTree::search(int id) {
    Node* result = search(root, id);
    if (result == nullptr) {
        return nullptr;
    }
    return &result->data;
}

void AVLTree::inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        std::cout << root->data.id << " (" << root->data.name << ")" << std::endl;
        inOrder(root->right);
    }
}

void AVLTree::inOrder() {
    inOrder(root);
}
