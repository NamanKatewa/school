#include "BuildingTree.h"
#include <iostream>
#include <iomanip>

BuildingTree::BuildingTree() : root(nullptr) {}

void BuildingTree::printTableHeader() const {
    std::cout << "+-" << std::string(12, '-') << "-+-" << std::string(20, '-') << "-+-" << std::string(30, '-') << "-+" << std::endl;
    std::cout << "| " << std::left << std::setw(12) << "Building ID"
              << "| " << std::left << std::setw(20) << "Building Name"
              << "| " << std::left << std::setw(30) << "Location Details"
              << " |" << std::endl;
    std::cout << "+-" << std::string(12, '-') << "-+-" << std::string(20, '-') << "-+-" << std::string(30, '-') << "-+" << std::endl;
}

void BuildingTree::printTableFooter() const {
    std::cout << "+-" << std::string(12, '-') << "-+-" << std::string(20, '-') << "-+-" << std::string(30, '-') << "-+" << std::endl;
}

BuildingNode* BuildingTree::insertBuilding(BuildingNode* node, const Building &b) {
    if (node == nullptr) {
        BuildingNode* newNode = new BuildingNode();
        newNode->data = b;
        newNode->left = newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (b.buildingID < node->data.buildingID) {
        node->left = insertBuilding(node->left, b);
    } else if (b.buildingID > node->data.buildingID) {
        node->right = insertBuilding(node->right, b);
    }

    return node;
}

void BuildingTree::insertBuilding(const Building &b) {
    root = insertBuilding(root, b);
}

void BuildingTree::inorderTraversal(BuildingNode* node) const {
    if (node != nullptr) {
        inorderTraversal(node->left);
        node->data.printRow();
        inorderTraversal(node->right);
    }
}

void BuildingTree::inorderTraversal() const {
    printTableHeader();
    inorderTraversal(root);
    printTableFooter();
}

void BuildingTree::preorderTraversal(BuildingNode* node) const {
    if (node != nullptr) {
        node->data.printRow();
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

void BuildingTree::preorderTraversal() const {
    printTableHeader();
    preorderTraversal(root);
    printTableFooter();
}

void BuildingTree::postorderTraversal(BuildingNode* node) const {
    if (node != nullptr) {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        node->data.printRow();
    }
}

void BuildingTree::postorderTraversal() const {
    printTableHeader();
    postorderTraversal(root);
    printTableFooter();
}
