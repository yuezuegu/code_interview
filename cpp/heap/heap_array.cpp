#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Heap{
private:
    vector<int> heap_arr{};

public:
    Heap(){
    }

    ~Heap(){
    }

    void add(int v){
        this->heap_arr.push_back(v);
        this->heapify_up(this->heap_arr.size()-1);
    }

    int pop(){
        int top_val = this->heap_arr[0];
        this->heap_arr[0] = this->heap_arr[this->heap_arr.size()-1];
        this->heap_arr.pop_back();
        heapify_down(0);

        return top_val;
    }

    void heapify_up(int child_ind){
        while(child_ind > 0){
            int parent_ind = this->parent_index(child_ind);
            if(this->heap_arr[child_ind] > this->heap_arr[parent_ind]){
                int tmp = this->heap_arr[parent_ind];
                this->heap_arr[parent_ind] = this->heap_arr[child_ind];
                this->heap_arr[child_ind] = tmp;
                child_ind = parent_ind;
            }
            else{
                return;
            }
        }
    }

    void heapify_down(int parent_ind){
        int child_ind_1 = this->child_index(parent_ind);
        int child_ind_2 = child_ind_1 + 1;

        if(child_ind_1 < this->heap_arr.size() && child_ind_2 < this->heap_arr.size()){
            int great_child_ind, lesser_child_ind;
            if(this->heap_arr[child_ind_1] > this->heap_arr[child_ind_2]){
                great_child_ind = child_ind_1;
                lesser_child_ind = child_ind_2;
            }
            else{
                great_child_ind = child_ind_2;
                lesser_child_ind = child_ind_1;
            }

            if(this->heap_arr[parent_ind] < this->heap_arr[great_child_ind]){
                int tmp = this->heap_arr[great_child_ind];
                this->heap_arr[great_child_ind] = this->heap_arr[parent_ind];
                this->heap_arr[parent_ind] = tmp; 
                heapify_down(great_child_ind);               
            }
            else if (this->heap_arr[parent_ind] < this->heap_arr[lesser_child_ind]){
                int tmp = this->heap_arr[lesser_child_ind];
                this->heap_arr[lesser_child_ind] = this->heap_arr[parent_ind];
                this->heap_arr[parent_ind] = tmp;       
                heapify_down(lesser_child_ind);           
            }
            else{
                return;
            }
        }
        else if(child_ind_1 < this->heap_arr.size()){
            if(this->heap_arr[parent_ind] < this->heap_arr[child_ind_1]){
                int tmp = this->heap_arr[child_ind_1];
                this->heap_arr[child_ind_1] = this->heap_arr[parent_ind];
                this->heap_arr[parent_ind] = tmp;           
            }
            else{
                return;
            }       
        }
        else{
            return;
        }
    }

    int parent_index(int child_ind){
        int level = (int)(log2(child_ind+1));
        int offset = child_ind + 1 - pow(2, level);
        return pow(2,level-1) + offset / 2 - 1;
    }

    int child_index(int parent_ind){
        int level = (int)(log2(parent_ind+1));
        int offset = parent_ind + 1 - pow(2, level);
        return pow(2,level+1) + offset*2 - 1;
    }

    void print(){
        int ind = 0;
        int level = 0;
        while(ind < this->heap_arr.size()){
            cout << this->heap_arr[ind] << " ";

            if (ind+1 == pow(2, level+1)-1){
                level++;
                cout << endl;
            }
            ind++;
        }
        cout << endl;
    }

};

int main(){
    Heap heap {};
    heap.add(19);
    heap.add(2);
    heap.add(1);
    heap.add(7);
    heap.add(3);
    heap.add(25);
    heap.add(100);
    heap.add(36);
    heap.add(17);
    
    heap.print();

    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;
    cout << "Popping: " << heap.pop() << endl;

    //heap.print();

    return 0;
}