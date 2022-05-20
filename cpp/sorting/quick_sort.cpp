#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void print_vector(vector<int> &vec){
    for(auto n : vec){
        cout << n <<" ";
    }
    cout << endl;
}

bool check_sorted(vector<int> &vec){
    for(int i = 1; i < vec.size(); i++){
        if(vec[i] < vec[i-1]){
            return false;
        }
    }
    return true;
}

vector<int> create_random_vector(const int array_len){
    vector<int> arr (array_len, 0);
    for(int i = 0; i < array_len; i++){
        arr[i] = rand() % 1000;
        cout << arr[i] << " ";
    }
    cout << endl;
    return arr;
}

vector<int>::iterator quick_sort(vector<int> &vec, vector<int>::iterator left, vector<int>::iterator right){
    int pivot = *left;

    while(left < right){
        if(*left >= pivot && *right <= pivot){
            int tmp = *right;
            *right = *left;
            *left = tmp;
            right--;
            left++;
        }
        else if(*left < pivot){
            left++;
        }
        else if(*right > pivot){
            right--;
        }
        else{
            left++;
            right--;
        }
    }

    if (left < right){
        return left;
    }
    else if (right < left){
        return right;
    }
    else{
        if(*left > pivot){
            return --left;
        }
        else{
            return left;
        }
    }
}

void sort_recursive(vector<int> &arr, vector<int>::iterator left, vector<int>::iterator right){
    if (left == right){
        return;
    }

    // cout << "Pivot: " << *(left + (right - left) / 2);

    auto mid = quick_sort(arr, left, right);

    // cout << " Left: " << left - arr.begin() << " Mid: " << mid - arr.begin() << " Right: " << right - arr.begin() << endl; 
    // print_vector(arr);
    // cout << endl;

    sort_recursive(arr, left, mid);
    sort_recursive(arr, mid+1, right);
}

int main(){
    //srand(0);

    const int array_len = 5000;
    
    cout << "Init array: " << endl;
    vector<int> arr = create_random_vector(array_len);
    sort_recursive(arr, arr.begin(), arr.end()-1);

    print_vector(arr);
    assert(check_sorted(arr));
    

    return 0;
}