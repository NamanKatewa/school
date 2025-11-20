#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <queue>

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode *root;

    void insert(TreeNode* &node, int value);
    bool search(TreeNode* node, int value) const;
    void preorder(TreeNode* node) const;
    void inorder(TreeNode* node) const;
    void postorder(TreeNode* node) const;
    void destroyTree(TreeNode* node);
    int height(TreeNode* node) const;
    int countNodes(TreeNode* node) const;
    int countLeaves(TreeNode* node) const;
    int countInternalNodes(TreeNode* node) const;
    TreeNode* minValueNode(TreeNode* node) const;
    TreeNode* maxValueNode(TreeNode* node) const;
    void mirror(TreeNode* node);
    void clear(TreeNode* &node);


public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);
    bool search(int value) const;

    void preorder() const;
    void inorder() const;
    void postorder() const;
    void levelOrder() const;

    int height() const;
    int countNodes() const;
    int countLeaves() const;
    int countInternalNodes() const;
    int minValue() const;
    int maxValue() const;

    void mirror();
    void clear();
};

#endif
