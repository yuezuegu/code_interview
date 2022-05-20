#include <iostream>

using namespace std;

struct Node_DLL{
    int value;
    Node_DLL* prev;
    Node_DLL* next;

    Node_DLL(int value) : value{value}, prev{nullptr}, next{nullptr} {}
    ~Node_DLL(){}

    void insert(Node_DLL* node){
        if(this->next == nullptr){
            this->next = node;
        }
        else{
            this->next->insert(node);
        }
    }
};

struct DLL{
    Node_DLL* root;

    DLL() : root{nullptr} {}
    ~DLL(){}

    void insert(Node_DLL* node){
        if(this->root == nullptr){
            this->root = node;
        }
        else{
            this->root->insert(node);
        }
    }
};


class Node_BST{
private:
    int value;
    Node_BST* left;
    Node_BST* right; 

public:
    Node_BST(int value)
        : value{value}, left{nullptr}, right{nullptr} {}
    ~Node_BST(){}

    int get_value(){return this->value;}

    void insert(Node_BST* node){
        if(node->get_value()>this->value){
            if(this->right == nullptr){
                this->right = node;
            }
            else{
                this->right->insert(node);
            }
        }
        else{
            if(this->left == nullptr){
                this->left = node;
            }
            else{
                this->left->insert(node);
            }
        }
    }

    void print(){        
        if(this->left == nullptr){
            //cout << "NULL";
        }
        else{
            this->left->print();
        }

        cout << " <- "<< this->value << " -> ";
        
        if(this->right == nullptr){
            //cout << "NULL";
        }
        else{
            this->right->print();
        }

    }
};

class BST{
private:
    Node_BST* root;

public:
    BST() : root{nullptr} {}

    void insert(int value){
        if(this->root == nullptr){
            this->root = new Node_BST(value);
        }
        else{
            this->root->insert(new Node_BST(value));
        }
    }

    void print_inorder(){
        if(this->root == nullptr){
            cout << "Empty tree" << endl;
        }
        else{
            this->root->print();
        }


    }
};





int main(){
    BST bst {};
    bst.insert(10);
    bst.insert(12);
    bst.insert(7);
    bst.insert(5);
    bst.insert(8);
    bst.insert(11);
    bst.insert(13);

    bst.print_inorder();


    return 0;
}