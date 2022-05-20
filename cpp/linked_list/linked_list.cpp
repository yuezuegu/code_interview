
#include <iostream>

using namespace std;

template <typename T>
class Node{
private:
    T val;
    Node<T>* forward;
    Node<T>* backward;

public:
    Node(T val){
        this->val = val;
        forward = nullptr;
        backward = nullptr;
    }

    void set_val(T val){
        this->val = val;
    }

    void set_forward(Node<T>* node){
        this->forward = node;
    }

    void set_backward(Node<T>* node){
        this->backward = node;
    }    

    T get_val(){
        return this->val;
    }

    void append(T new_val){
        if(this->forward == nullptr){
            this->forward = new Node(new_val);
            this->forward->set_backward(this);
        }
        else{
            this->forward->append(new_val);
        }
    }

    Node<T>* find_back(){
        if (this->backward == nullptr) {
            return this;
        }
        else {
            return this->backward->find_back();
        }
    }

    Node<T>* remove(T val){
        //cout << this->val << endl;
        if (this->val == val){
            if (this->forward != nullptr) {
                this->forward->set_backward(this->backward);
            }

            if (this->backward != nullptr) {
                this->backward->set_forward(this->forward);
            }

            //cout << "FWD: " << this->forward->get_val() << endl;
            //cout << "BCK: " << this->backward->get_val() << endl;

            Node<T>* head = this->forward;

            delete this;
            return head;
        }
        else if(this->forward != nullptr){
            this->forward->remove(val);
        }
        return this;
    }

    Node<T>* advance(int no_steps = 1){
        if (no_steps == 0){
            return this;
        }
        else if (this->forward == nullptr){
            return nullptr;
        }
        else{
            return this->forward->advance(no_steps-1);
        }
    }

    void print(){
        cout << this->val;
        if (this->forward != nullptr){
            cout << " -> ";
            this->forward->print();
        }
        else{
            cout << endl;
        }
    }

    ~Node(){
        this->forward = nullptr;
        this->backward = nullptr;
    }

};



int main(){

    Node<int>* list = new Node<int> (3);
    list->append(5);
    list->append(1);
    list->append(7);
    list->append(5);
    list->append(2);

    list->print();

    Node<int>* it = list->advance(1);
    it->print();

    it = it->advance(3);    
    it->print();

    return 0;
}