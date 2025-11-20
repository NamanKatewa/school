#include "BinarySearchTree.hpp"
#include <stdexcept>
#include <queue>
#include <algorithm>

void BinarySearchTree::insert(TreeNode* &node, int value) {
    if (node == nullptr) {
        node = new TreeNode(value);
    } else if (value < node->data) {
        insert(node->left, value);
    } else if (value > node->data) {
        insert(node->right, value);
    }
}

bool BinarySearchTree::search(TreeNode* node, int value) const {
    if (node == nullptr) {
        return false;
    }
    if (value == node->data) {
        return true;
    }
    return value < node->data ? search(node->left, value) : search(node->right, value);
}

void BinarySearchTree::preorder(TreeNode* node) const {
    if (node != nullptr) {
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void BinarySearchTree::inorder(TreeNode* node) const {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
}

void BinarySearchTree::postorder(TreeNode* node) const {
    if (node != nullptr) {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
}

void BinarySearchTree::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int BinarySearchTree::height(TreeNode* node) const {
    if (node == nullptr) {
        return -1;
    }
    return 1 + std::max(height(node->left), height(node->right));
}

int BinarySearchTree::countNodes(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BinarySearchTree::countLeaves(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    return countLeaves(node->left) + countLeaves(node->right);
}

int BinarySearchTree::countInternalNodes(TreeNode* node) const {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
        return 0;
    }
    return 1 + countInternalNodes(node->left) + countInternalNodes(node->right);
}

TreeNode* BinarySearchTree::minValueNode(TreeNode* node) const {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

TreeNode* BinarySearchTree::maxValueNode(TreeNode* node) const {
    TreeNode* current = node;
    while (current && current->right != nullptr) {
        current = current->right;
    }
    return current;
}

void BinarySearchTree::mirror(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    std::swap(node->left, node->right);
    mirror(node->left);
    mirror(node->right);
}

void BinarySearchTree::clear(TreeNode* &node) {
    destroyTree(node);
    node = nullptr;
}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::insert(int value) {
    insert(root, value);
}

bool BinarySearchTree::search(int value) const {
    return search(root, value);
}

void BinarySearchTree::preorder() const {
    preorder(root);
    std::cout << std::endl;
}

void BinarySearchTree::inorder() const {
    inorder(root);
    std::cout << std::endl;
}

void BinarySearchTree::postorder() const {
    postorder(root);
    std::cout << std::endl;
}

void BinarySearchTree::levelOrder() const {
    if (root == nullptr) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        std::cout << current->data << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    std::cout << std::endl;
}

int BinarySearchTree::height() const {
    return height(root);
}

int BinarySearchTree::countNodes() const {
    return countNodes(root);
}

int BinarySearchTree::countLeaves() const {
    return countLeaves(root);
}

int BinarySearchTree::countInternalNodes() const {
    return countInternalNodes(root);
}

int BinarySearchTree::minValue() const {
    TreeNode* node = minValueNode(root);
    if (node == nullptr) throw std::logic_error("Tree is empty.");
    return node->data;
}

int BinarySearchTree::maxValue() const {
    TreeNode* node = maxValueNode(root);
    if (node == nullptr) throw std::logic_error("Tree is empty.");
    return node->data;
}

void BinarySearchTree::mirror() {
    mirror(root);
}

void BinarySearchTree::clear() {
    clear(root);
}
