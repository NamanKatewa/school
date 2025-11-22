#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <string>
#include <vector>

struct ExprNode {
    std::string value;
    ExprNode *left;
    ExprNode *right;
};

class ExpressionTree {
private:
    ExprNode *root;
    double evaluate(ExprNode* node) const;
    void printInorder(ExprNode* node) const;

public:
    ExpressionTree();
    void buildFromPostfix(const std::vector<std::string> &tokens);
    double evaluate() const;
    void printInorder() const;
};

#endif
