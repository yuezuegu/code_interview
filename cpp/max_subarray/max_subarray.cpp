#include <iostream>
#include <vector>

using namespace std;


int max_subarray(vector<int> &nums){
    auto max_first = nums.begin();
    auto max_last = nums.begin();
    auto last = nums.begin()+1;

    int curr_slice_val = nums[0];
    int max_slice_val = nums[0];
    
    while(last != nums.end()){
        if (curr_slice_val < 0){
            curr_slice_val = *last;
            max_first = last;
        }
        else{
            curr_slice_val += *last;
        }

        if (curr_slice_val > max_slice_val){
            max_slice_val = curr_slice_val;
            max_last = last;
        }

        last++;
    }

    cout << "Max. subarray value: " << max_slice_val << " starting " << max_first-nums.begin() << " ending " << max_last-nums.begin() << endl;
    return max_slice_val;
}

int main(){
    vector<int> nums {-3,1,-8,4,-1,2,1,-5,5};
    max_subarray(nums);

    nums = {-3};
    max_subarray(nums);

    nums = {-3, -1, -5, 8, 1, -3, 7};
    max_subarray(nums);

    return 0;
}