#include <iostream>

using namespace std;


class Node{
private:
    int value;
    int level;
    Node* parent;
    Node* left;
    Node* right;

public:
    Node(int value, int level, Node* parent){
        this->value = value;
        this->level = level;
        this->parent = parent;
        this->left = nullptr;
        this->right = nullptr;
    }

    int get_value(){ return this->value;}

    void add(int value){
        if(value == this->value){
            return;
        }
        else if(value < this->value){
            if(this->left == nullptr){
                this->left = new Node(value, this->level+1, this);
            }
            else {
                this->left->add(value);
            }
        }
        else {
            if(this->right == nullptr){
                this->right = new Node(value, this->level+1, this);
            }
            else{
                this->right->add(value);
            }
        }
    }

    void remove(int value){
        if(this->value == value){
            if(this->left == nullptr && this->right == nullptr){

            }
        }
        else if(value < this->value){

        }
        else{

        }
    }

    int find_and_remove_smallest(){
        if(this->left == nullptr){
            if (this->right != nullptr){
                if(this->parent != nullptr){
                    this->parent->left = this->right;
                }
            }
            return this->value;
        }
        else{
            return this->left->find_and_remove_smallest();
        }
    }

    friend ostream& operator<< (ostream& os, const Node &node);
};

ostream& operator<< (ostream& os, const Node &node){
    for(int i = 0; i<node.level; i++){
        cout << "\t";
    }

    if(node.left != nullptr){
        os << node.left->value << " <- ";
    }

    os << node.value << " -> ";

    if(node.right != nullptr){
        os << node.right->value << " ";
    }

    os << endl;

    if(node.left != nullptr){
        os << *(node.left) << " ";
    }
    if(node.right != nullptr){
        os << *(node.right) << " ";
    }

    return os;
}

class BST{
private:
    Node* root;

public:
    
    BST(){
        this->root = nullptr;
    }

    void add(int value){
        if(this->root == nullptr){
            this->root = new Node(value, 0, nullptr);
        }
        else{
            this->root->add(value);
        }
    }

    void remove(int value){
        if(this->root == nullptr){
            return;
        }
        else{
            this->root->remove(value);
        }
    }

    friend ostream& operator<< (ostream &os, const BST &bst);

};

ostream& operator<< (ostream &os, const BST &bst){
    os << *(bst.root);
    return os;
}

int main(){
    BST bst {};
    bst.add(3);
    bst.add(15);
    bst.add(21);
    bst.add(1);
    bst.add(5);
    bst.add(7);
    bst.add(-3);
    bst.add(-8);
    
    cout << bst;


    return 0;
}