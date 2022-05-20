
#include <iostream>
#include <climits>

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

    ~Node(){}

    void push_back(int value){
        if(this->next == nullptr){
            this->next = new Node(value);
        }
        else{
            this->next->push_back(value);
        }
    }

    bool is_last_node(){
        return this->next == nullptr;
    }

    int get_value(){
        return this->value;
    }

    int pop_back(){
        if(this->next->is_last_node()){
            int val = this->next->get_value();
            delete this->next;
            this->next = nullptr;
            return val;
        }
        else{
            int val = this->next->pop_back();
            // cout << "Node: " << this->value << " Returning: " << val << endl;
            return val;
        }
    }

    void print(){
        cout << this->value << " ";
        if (this->next != nullptr){
            this->next->print();
        }
        else{
            cout << endl;
        }
    }
};

class List{
private:
    Node* head;
    int node_cnt;


public:
    List(){
        this->head = nullptr;
        this->node_cnt = 0;
    }

    ~List(){}

    void push_back(int value){
        if(this->head == nullptr){
            this->head = new Node(value);
        }
        else{
            this->head->push_back(value);
        }
        this->node_cnt++;
    }

    int pop_back(){
        if(this->head == nullptr){
            cerr << "List is empty" << endl;
            return -1;
        }
        else if(this->head->is_last_node()){
            int val = this->head->get_value();
            delete this->head;
            this->head = nullptr;
            this->node_cnt--;
            return val;
        }
        else{
            this->node_cnt--;
            return this->head->pop_back();
        }
    }

    int get_size(){
        return this->node_cnt;
    }

    void print(){
        this->head->print();
    }

};

class MinStack{
private:
    List* list;
    int min_value;

public:
    MinStack(){
        this->list = new List();
    }

    ~MinStack(){}

    void push(int value){
        if (this->list->get_size() == 0){
            this->min_value = value;
            this->list->push_back(value);
        }
        else{
            if(value <= this->min_value){
                this->list->push_back(2*value - this->min_value);
                this->min_value = value;
            }
            else{
                this->list->push_back(value);
            }
        }
    }

    int pop(){
        if(this->list->get_size() == 0){
            cerr << "Stack is empty" << endl;
            return -1;
        }
        else if (this->list->get_size() == 1){
            return this->list->pop_back();
        }
        else{
            int pop_val = this->list->pop_back();
            if (pop_val <= this->min_value){
                int out_val = this->min_value;
                this->min_value = 2 * this->min_value - pop_val;
                return out_val;
            }
            else{
                return pop_val;
            }
        }
    }

    int peek_min(){
        return this->min_value;
    }

    void print(){
        this->list->print();
    }
};



int main(){

    MinStack min_stack{};

    // min_stack.push(2);
    // cout << "Peeking: " << min_stack.peek_min() << endl;
    // cout << "Popping: " << min_stack.pop() << endl;

    min_stack.push(15);
    min_stack.push(7);
    min_stack.push(8);
    min_stack.push(9);
    min_stack.push(3);
    min_stack.push(6);
    min_stack.push(11);
    min_stack.push(13);
    min_stack.push(12);

    min_stack.print();

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;    

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;    

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;    

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;    

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;    

    cout << "Peeking: " << min_stack.peek_min() << endl;
    cout << "Popping: " << min_stack.pop() << endl;    
    
    return 0;
}