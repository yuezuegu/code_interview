#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

struct Node{
public:
    int value;
    Node* next;
    pthread_mutex_t mutex1;

    Node(int value) : value{value}, next{nullptr} {pthread_mutex_init(&(this->mutex1), NULL);}
    ~Node(){}

    void add(int val){
        pthread_mutex_lock(&(this->mutex1));
        bool is_next_null = this->next == nullptr;

        if(is_next_null){
            this->next = new Node(val);
            pthread_mutex_unlock(&(this->mutex1));
        }
        else{
            pthread_mutex_unlock(&(this->mutex1));
            this->next->add(val);
        }
    }

    void remove(int val){
        if (this->next == nullptr){
            return;
        }
        else if(this->next->value == val){
            Node *tmp = this->next->next;
            delete this->next;
            this->next = this->next->next;
        }
        else{
            this->next->remove(val);
        }
    }

    bool contains(int val){
        if (this->value == val){
            return true;
        }
        else if (this->next == nullptr){
            return false;
        }
        else{
            return this->next->contains(val);
        }
    }

    void print(){
        cout << this->value;
        if (this->next != nullptr){
            cout << " -> ";
            this->next->print();
        }
    }
};

class List{
private:
    Node* root;
    pthread_mutex_t mutex1;

public:
    List() : root{nullptr} {pthread_mutex_init(&(this->mutex1), NULL);}
    
    void add(int val){
        pthread_mutex_lock(&(this->mutex1));
        //cout << "Thread: "<< pthread_self() << " val: " << val << endl;

        bool is_root_null = this->root == nullptr;

        if (is_root_null){
            this->root = new Node(val);
            pthread_mutex_unlock(&(this->mutex1));
        }
        else{
            pthread_mutex_unlock(&(this->mutex1));
            this->root->add(val);
        }
        //pthread_mutex_unlock(&(this->mutex1));
    }

    void remove(int val){
        if (this->root == nullptr){
            return;
        }
        else if(this->root->value == val){
            Node *tmp = this->root->next;
            delete this->root;
            this->root = tmp;
        }
        else{
            this->root->remove(val);
        }
    }

    bool contains(int val){
        if (this->root == nullptr){
            return false;
        }
        else{
            return this->root->contains(val);
        }
    }

    void print(){
        if (this->root == nullptr){
            cout << "Empty list" << endl;
        }
        else{
            this->root->print();
        }
        cout << endl;
    }
};

struct thread_args{
    int val;
    List* list_ptr;  

    thread_args(int val, List* list_ptr) : val{val}, list_ptr{list_ptr} {}; 
};

void* insert(void* args){
    thread_args* t_args = (thread_args*)args;
    int val = t_args->val;
    List* list = t_args->list_ptr;

    list->add(val);

    delete t_args;
}

int main(){
    const int no_vals = 20;
    int rnd_vals [no_vals] {};
    for (int i = 0; i < no_vals; i++){
        rnd_vals[i] = rand() % 100;
    }

    List* list1 = new List();
    for (int i = 0; i < no_vals; i++){
        list1->add(rnd_vals[i]);
    }
    list1->print();

    const int no_threads = no_vals;
    pthread_t threads[no_threads];
    const pthread_attr_t * attr = NULL;

    List* list2 = new List();
    for (int i = 0; i < no_threads; i++){
        thread_args* args = new thread_args(rnd_vals[i], list2);
        pthread_create(&threads[i], attr, insert, (void*) args );
    }

    for (int i = 0; i < no_threads; i++)
        pthread_join(threads[i], NULL);

    
    list2->print();

    return 0;
}