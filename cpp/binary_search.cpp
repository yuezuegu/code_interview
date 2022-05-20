#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

bool binary_search(vector<int> &vec, int key){
    vector<int>::iterator left = vec.begin();
    vector<int>::iterator right = vec.end()-1;
    vector<int>::iterator mid {};

    while(right > left){
        mid = left + (right - left) / 2;
        if (*mid == key){
            return true;
        }
        else if (*mid < key){
            left = mid+1;
        }
        else{
            right = mid-1;
        }
    }    

    if(*right == key){
        return true;
    }
    else{
        return false;
    }
}



int main(){
    vector<int> vec {0,1,2,3,4,5,6,7,8};

    cout << binary_search(vec, 9) << endl;
    
    return 0;
}