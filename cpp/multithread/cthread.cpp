#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

mutex mux;

void func(int id, int& sum){
    // cout << "Thread: " << id << " " << this_thread::get_id() << endl;

    mux.lock();
    int sum_val = sum;
    this_thread::sleep_for(chrono::microseconds(1));
    sum = sum_val + 1;
    mux.unlock();
}

int main(){
    const int no_threads = 100;

    vector<thread> th;

    int sum = 0;

    for (int i = 0; i < no_threads; i++){
        th.push_back( thread(&func, i, ref(sum)) );
    }
    
    //cout << "Main thread" << endl;

    for (int i = 0; i < no_threads; i++){
        th[i].join();
    }

    cout << "Sum: " << sum << endl;

    return 0;
}