#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;


struct Node{
    int value;
    Node* next;
    Node* prev;
    mutex mut;

    Node(int value) : value{value}, next{nullptr}, prev{nullptr} {}
    ~Node(){}

    void insert(Node* node){
        this->prev->mut.lock();
        this->mut.lock();

        if (node->value <= this->value){
            this->prev->next = node;

            node->next = this;
            node->prev = this->prev;
            this->prev = node;

            
            this->mut.unlock();
            this->prev->prev->mut.unlock();            
        }
        else{
            if(this->next == nullptr){
                this->next = node;
                node->prev = this;

                this->mut.unlock();
                this->prev->mut.unlock();
            }
            else{
                this->mut.unlock();
                this->prev->mut.unlock();

                this->next->insert(node);
            }
        }
    }

    void erase(int value){
        this->prev->mut.lock();
        this->mut.lock();
        if(value == this->value){
            this->prev->next = this->next;
            if(this->next != nullptr){
                this->next->prev = this->prev;
            }
            this->mut.unlock();
            this->prev->mut.unlock();
            //delete this;
        }
        else if(value < this->value){
            this->mut.unlock();
            this->prev->mut.unlock();
            return;
        }
        else if(this->next == nullptr){
            this->mut.unlock();
            this->prev->mut.unlock();
            return;
        }
        else{
            this->mut.unlock();
            this->prev->mut.unlock();
            this->next->erase(value);
        }
    }

    bool exist(int value){
        if(value < this->value){
            return false;
        }
        else if(value == this->value){
            return true;
        }
        else if(this->next == nullptr){
            return false;
        }
        else{
            return this->next->exist(value);
        }
    }

    void print(){
        cout << this->value << " -> ";
        if(this->next != nullptr){
            this->next->print();
        }
    }
};

struct List{
    Node* root;

    List() : root{new Node(-1)} {}
    ~List(){}

    void insert(int value){
        Node* node = new Node(value);
        this->root->mut.lock();
        if(this->root->next == nullptr){
            this->root->next = node;
            node->prev = this->root;

            this->root->mut.unlock();
        }
        else{
            this->root->mut.unlock();
            this->root->next->insert(node);
        }
    }

    void erase(int value){
        this->root->mut.lock();
        if(this->root->next != nullptr){
            this->root->next->erase(value);
        }
        this->root->mut.lock();
    }

    bool exist(int value){
        if(this->root->next == nullptr){
            return false;
        }
        else{
            return this->root->next->exist(value);
        }
    }

    void print(){
        if(this->root->next == nullptr){
            cout << "Empty list" << endl;
        }
        else{
            this->root->next->print();
            cout << endl;
        }
    }
};


void writer(List &list){
    int ticket = 0;

    while(ticket < 10){
        list.insert(ticket);
        ticket++;
    }

}

void eraser(List &list){
    int ticket = 0;

    while(ticket < 10){
        list.erase(ticket);
        ticket++;
    }
}


int main(){
    List list {};

    const int no_writer = 10;
    
    vector<thread> th_reader;
    vector<thread> th_writer;
    vector<thread> th_eraser;

    for(int i = 0; i < no_writer; i++){
        th_writer.push_back(thread(&writer, ref(list)));
        th_eraser.push_back(thread(&eraser, ref(list)));
    }

    for(int i = 0; i < no_writer; i++){
        th_writer[i].join();
    }    

    list.print();

    
    // list.insert(5);
    // list.insert(7);
    // list.insert(6);
    // list.insert(3);

    // list.print();

    // cout << list.exist(7) << endl;
    // cout << list.exist(5) << endl;
    // cout << list.exist(3) << endl;
    // cout << list.exist(4) << endl;

    // list.erase(6);
    // list.print();

    // list.erase(3);
    // list.print();

    // list.erase(7);
    // list.print();

    return 0;
}