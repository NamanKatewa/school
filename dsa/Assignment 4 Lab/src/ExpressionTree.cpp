#include "ExpressionTree.h"
#include <stack>
#include <stdexcept>
#include <iostream>

ExpressionTree::ExpressionTree() : root(nullptr) {}

bool isOperator(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

void ExpressionTree::buildFromPostfix(const std::vector<std::string> &tokens) {
    std::stack<ExprNode*> s;
    for (const auto& token : tokens) {
        ExprNode* newNode = new ExprNode{token, nullptr, nullptr};
        if (isOperator(token)) {
            newNode->right = s.top(); s.pop();
            newNode->left = s.top(); s.pop();
        }
        s.push(newNode);
    }
    root = s.top();
}

double ExpressionTree::evaluate(ExprNode* node) const {
    if (!node) return 0;
    if (!isOperator(node->value)) {
        return std::stod(node->value);
    }
    
    double leftVal = evaluate(node->left);
    double rightVal = evaluate(node->right);

    if (node->value == "+") return leftVal + rightVal;
    if (node->value == "-") return leftVal - rightVal;
    if (node->value == "*") return leftVal * rightVal;
    if (node->value == "/") {
        if (rightVal == 0) throw std::runtime_error("Division by zero");
        return leftVal / rightVal;
    }
    return 0;
}

double ExpressionTree::evaluate() const {
    if (!root) return 0;
    return evaluate(root);
}

void ExpressionTree::printInorder(ExprNode* node) const {
    if (!node) return;
    if (isOperator(node->value)) std::cout << "(";
    printInorder(node->left);
    std::cout << " " << node->value << " ";
    printInorder(node->right);
    if (isOperator(node->value)) std::cout << ")";
}

void ExpressionTree::printInorder() const {
    if (!root) return;
    printInorder(root);
    std::cout << std::endl;
}
