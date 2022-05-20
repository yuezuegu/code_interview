#include <iostream>
#include <cmath>

using namespace std;


class Node {
    
private:
    int val;
    int level;
    Node* left;
    Node* right;
    Node* parent;
    
public:
    static int no_nodes;
    static int max_level;
    
    Node(int val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->level = 0;
    }

    ~Node(){
        // cout << "Destructing: " << this->val << " No of nodes: "<< no_nodes << " Max level: "<< max_level <<endl;
        if(this->left != nullptr)
            delete this->left;
        if(this->right != nullptr)
            delete this->right;
        if(this->parent != nullptr){
            if(this->parent->left == this)
                this->parent->left = nullptr;
            if(this->parent->right == this)
                this->parent->right = nullptr;            
        }
       
        if(no_nodes == pow(2,max_level)){
            max_level--;
            // cout << "Max. level: " << max_level << endl;
        }
        no_nodes--;
    }
    
    void set_left(Node* node){
        this->left = node;
        this->left->set_level(this->level+1);
        this->left->set_parent(this);
        no_nodes++;
    }
    
    void set_right(Node* node){
        this->right = node;
        this->right->set_level(this->level+1);
        this->right->set_parent(this);
        no_nodes++;
    }

    void set_parent(Node* node){
        this->parent = node;
    }
    
    void set_val(int val){
        this->val = val;
    }
    
    void set_level(int level){
        this->level = level;
        if (this->level > this->max_level){
            this->max_level = this->level;
        }
    }
    
    Node* get_left(){
        return this->left;
    }
    
    Node* get_right(){
        return this->right;
    }
    
    Node* get_parent(){
        return this->parent;
    }
    
    int get_val(){
        return this->val;
    }
    
    int get_level(){
        return this->level;
    }
    
    bool insert(Node* node){
        if (this->left == nullptr){
            set_left(node);
            this->left->heapify_up();
            return true;
        }
        else if (this->right == nullptr){
            set_right(node);
            this->right->heapify_up();
            return true;
        }
        else{
            if(this->level == this->max_level - 1){
                //cout << "Inserting " << node->get_val() << " Level: " << this->level << " Max level: " << this->max_level << endl;
                if (this->is_full()){
                    //cout << "Tree is full" << endl;
                    this->left->insert(node);
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                if (this->left->insert(node)){
                    return true;
                }
                else if (this->right->insert(node)){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
    
    
    pair<bool, int> find_and_remove_leaf(){
        if (this->level == max_level){
            int leaf_val = this->val;
            // cout << "Deleting node: " << leaf_val << endl;
            delete this;
            return pair<bool, int>(true, leaf_val);
        }
        else{
            pair<bool, int> res;
            if(this->left != nullptr) {
                res = this->left->find_and_remove_leaf();
                if (res.first){ return res;}
            }
            
            if(this->right != nullptr) {
                res = this->right->find_and_remove_leaf();
                if (res.first){ return res;}
            }

            return pair<bool, int>(false, 0);
        }
    }
    
    int pop(){
        int val = this->val;
        int leaf_val;
        
        auto res = find_and_remove_leaf();
        if (res.first){leaf_val = res.second;}
        else {cout << "Something wrong" << endl;} 
        
        //cout << "No. of nodes: " << no_nodes << endl;
        if (no_nodes > 0){
            set_val(leaf_val);
            heapify_down();
        }
        return val;
    }
    
    
    void heapify_up(){
        if (this->parent == nullptr){
            //cout << "Root is reached." << endl;
            return;
        }
        if (this->val > this->parent->get_val()){
            int tmp = this->val;
            this->val = this->parent->get_val();
            this->parent->set_val(tmp);
            this->parent->heapify_up();
        }
    }
    
    void heapify_down(){
        int left_val, right_val, tmp_val;
        if (this->left != nullptr && this->right != nullptr){
            left_val = this->left->get_val();
            right_val = this->right->get_val();
            if (left_val > right_val){
                if (left_val > this->val){
                    tmp_val = this->val;
                    set_val(left_val);
                    this->left->set_val(tmp_val);
                    this->left->heapify_down();
                }
            }
            else{
                if (right_val > this->val){
                    tmp_val = this->val;
                    set_val(right_val);
                    this->right->set_val(tmp_val);
                    this->right->heapify_down();
                }
            }
        }
        else if(this->left != nullptr){
            left_val = this->left->get_val();
            if (left_val > this->val){
                tmp_val = this->val;
                set_val(left_val);
                this->left->set_val(tmp_val);
                this->left->heapify_down();
            }            
        }
        else if(this->right != nullptr){
            right_val = this->right->get_val();
            if (right_val > this->val){
                tmp_val = this->val;
                set_val(right_val);
                this->right->set_val(tmp_val);
                this->right->heapify_down();
            }
        }
    }
    
    friend ostream& operator<<(ostream& os, const Node* node){
        if (no_nodes == 0) {return os << "Empty tree";}
        
        for(int i =0; i< node->level; i++){
            os << "\t";
        }
        
        //os << "Level: " << node.level << "\tValue: " << node.val;
        os << node->val;
        if (node->left != nullptr){
            os << endl << node->left;
        }
        if (node->right != nullptr){
            os << endl << node->right;
        }        
        return os;
    }
    
    static int is_full(){
        // cout << "No nodes: " << no_nodes << " max_level: " << max_level << endl;
        return no_nodes == pow(2,max_level+1)-1;
    }
};

int Node::no_nodes = 0;
int Node::max_level = 0;

// To execute C++, please define "int main()"
int main() {
    Node* root = new Node(15);
    Node::no_nodes++;
    
    root->insert(new Node(13));
    root->insert(new Node(9));
    root->insert(new Node(10));
    root->insert(new Node(8));
    root->insert(new Node(5));
    root->insert(new Node(12));
    root->insert(new Node(11));
    root->insert(new Node(20));
    root->insert(new Node(9));

    cout << root << endl;
    
    int loop_range = Node::no_nodes;
    for (int i = 0; i < loop_range; i++){
        cout << "Popped: " << root->pop() << endl;
    }

    cout << root << endl;
    cout << "Finished." << endl;
    return 0;
}
