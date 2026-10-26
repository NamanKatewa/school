#include <iostream>
using namespace std;

class Node{
    public:
        int data;
        Node *left;
        Node *right;

        Node(int value){
            data = value;
            left = right = nullptr;
        }
};

class BinaryTree{
    private:
        Node *root;

        Node* insert(Node* node, int key){
            if(node ==nullptr){
                return new Node(key);
            }

            if(key < node->data){
                node->left = insert(node->left, key);
            }else if(key > node->data){
                node->right = insert(node->right, key);
            }

            return node;
        }

        void inorder(Node* node){
            if (node==nullptr){
                return;
            }

            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }

        void preorder(Node* node){
            if(node ==nullptr){
                return;
            }
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }

        int height(Node* node){
            if(node==nullptr){
                return 0;
            }
            int lHeight = height(node->left);
            int rHeight = height(node->right);
            return 1 + max(lHeight, rHeight);
        }

    public:
        BinaryTree(){
            root = nullptr;
        }

        void insert(int key){
            root = insert(root, key);
        }

        void displayInorder(){
            inorder(root);
            cout << endl;
        }

        int getHeight(){
            return height(root);
        }
};