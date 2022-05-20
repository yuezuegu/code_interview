#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


int main(){
    vector<int> nums {1,7,4,3,4,8,7,4,3,6,5,1,4,7,8,7,7};

    unordered_map<int, int> no_occurs {};
    int max_occur_val = 0;
    int max_occur_num = -1;

    for (int n : nums){
        if (no_occurs.count(n) == 0){
            no_occurs[n] = 1;
        }
        else{
            no_occurs[n]++; 
        }

        if(no_occurs[n] > max_occur_val){
            max_occur_val = no_occurs[n];
            max_occur_num = n;
        }
    }

    cout << max_occur_num << " occurs " << max_occur_val << " times. "<< endl;

    return 0;
}