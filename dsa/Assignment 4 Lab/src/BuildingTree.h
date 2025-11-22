#ifndef BUILDINGTREE_H
#define BUILDINGTREE_H

#include "Building.h"

struct BuildingNode {
    Building data;
    BuildingNode *left;
    BuildingNode *right;
    int height;
};

class BuildingTree {
private:
    BuildingNode *root;

    BuildingNode* insertBuilding(BuildingNode* node, const Building &b);
    void inorderTraversal(BuildingNode* node) const;
    void preorderTraversal(BuildingNode* node) const;
    void postorderTraversal(BuildingNode* node) const;
    void printTableHeader() const;
    void printTableFooter() const;

public:
    BuildingTree();
    void insertBuilding(const Building &b);
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
};

#endif
