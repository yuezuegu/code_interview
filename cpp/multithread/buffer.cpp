

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

int max_buff_size = 50;

struct Node{
    int value;
    Node* next;

    Node(int value) : value{value}, next{nullptr} {}
    ~Node(){}

    void insert(Node* node){
        if(this->next == nullptr){
            this->next = node;
        }
        else{
            this->next->insert(node);
        }
    }
};

struct Buffer{
    Node* root;
    int size;
    mutex mut;

    Buffer() : root{nullptr}, size{0} {}
    ~Buffer(){}

    void push(int value){
        if(this->root == nullptr){
            this->root = new Node(value);
        }
        else{
            this->root->insert(new Node(value));
        }
        
        size++;
    }

    int pop(){
        int out_val;

        if(this->root == nullptr){
            cerr << "Buffer is empty." << endl;
            throw 0;
        }
        else{
            Node* head = this->root;
            this->root = head->next;
            out_val = head->value;
            delete head;
        }

        size--;

        return out_val;
    }

    int get_size(){ 
        int val = this->size;
        return val;
    }
};

mutex mut;
condition_variable cv;


void producer(Buffer &buff){
    int ticket = 0;
    while(true){
        unique_lock<mutex> lock(mut);
        cv.wait(lock, [&](){return buff.get_size() < max_buff_size;});

        int val = ticket;
        buff.push(val);
        cout << "Producing: " << val << endl;
        ticket++;

        lock.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(Buffer &buff){
    while(true){
        unique_lock<mutex> lock(mut);
        cv.wait(lock, [&](){return buff.get_size() > 0;});

        int val = buff.pop();
        cout << "Consuming: " << val << endl;

        lock.unlock();
        cv.notify_one();
        //this_thread::sleep_for(chrono::milliseconds(1));
    }
}


int main(){
    Buffer buff{};

    const int no_threads = 20;

    vector<thread> th_pro;
    vector<thread> th_con ;

    for(int i = 0; i < no_threads; i++){
        th_pro.push_back(thread(&producer, ref(buff)));
        th_con.push_back(thread(&consumer, ref(buff)));
    }

    for(int i = 0; i < no_threads; i++){
        th_pro[i].join();
        th_con[i].join();
    }
    return 0;
}