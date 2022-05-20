#include <iostream>
#include<cmath>

using namespace std;

int logx (long num, unsigned base){
    int res = 0;
    while(num>1){
        num = num/base;
        res++;
    }
    return res;
}

int* aligned_malloc(size_t size, unsigned base){
    int* ptr;
    ptr++;
    long ptr_addr = reinterpret_cast<long>(ptr);
    long ptr_addr_ceil;
    if (ptr_addr % base == 0)
        ptr_addr_ceil = ptr_addr;
    else
        ptr_addr_ceil = (long)(base * (ptr_addr / base + 1));

    ptr += (ptr_addr_ceil - ptr_addr) / sizeof(int);

    cout << hex;
    cout << ptr_addr << endl;
    cout << ptr_addr_ceil << endl;

    ptr = new int[size];

    cout << ptr << endl;
    cout << dec;

    return ptr;
}



int main(){
    aligned_malloc(1000, 128);
    return 0;
}