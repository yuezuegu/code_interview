
#include <iostream>

using namespace std;

class Node{
private:
    int value;
    Node* next;
public:
    Node(int value){
        this->value = value;
        this->next = nullptr;
    }

    Node* get_next(){
        return this->next;
    }

    void set_next(Node* next){
        this->next = next;
    }

    void print(){
        cout << this->value << " -> ";
    }

    ~Node(){}
};

class List{
private:
    Node* root;

public:
    List(){
        this->root = nullptr;
    }

    void append(Node* node){
        if(this->root == nullptr){
            this->root = node;
        }
        else{
            Node* curr_node = this->root;
            while(curr_node->get_next() != nullptr){
                curr_node = curr_node->get_next();
            }
            curr_node->set_next(node);
        }
    }

    void print(){
        if(this->root == nullptr){
            cout << "Empty list" << endl;
        }
        else{
            Node* curr_node = this->root;
            while(curr_node != nullptr){
                curr_node->print();
                curr_node = curr_node->get_next();
            }
        }
    }

    void reverse_k(int k){
        Node* tail = this->root;
        Node* curr = tail;
        Node* next;

        int cnt = 0;
        while(cnt < k-1){
            next = curr->get_next();
            if(next == nullptr){ break;}

            curr->set_next(next->get_next());

            next->set_next(tail);
            tail = next;

            cnt++;
        }
        this->root = tail;

        Node* head = curr;

        next = curr->get_next();
        while(next != nullptr){
            tail = next;
            curr = next;
            cnt = 0;
            while(cnt < k-1){
                next = curr->get_next();
                //next->print();

                if(next == nullptr){ break;}

                curr->set_next(next->get_next());

                next->set_next(tail);
                tail = next;

                cnt++;
            }
            head->set_next(tail);
            head = curr;
            next = curr->get_next();
        }

        cout << "Reversing done." << endl;
    }

};

int main(){
    List list {};

    list.append(new Node(1));
    list.append(new Node(2));
    list.append(new Node(3));
    list.append(new Node(4));
    list.append(new Node(5));
    list.append(new Node(6));
    list.append(new Node(7));
    list.append(new Node(8));

    list.reverse_k(3);

    list.print();


    return 0;
}