#include <iostream>
#include <vector>

using namespace std;

int knapsack(vector<int> &vals, vector<int> &w, int weight_lim, int ind=0, int total_val=0){
    int max_val = total_val;
    for (int i = ind; i < vals.size(); i++){
        if(w[i]<=weight_lim){
            int out = knapsack(vals, w, weight_lim-w[i], i+1, total_val+vals[i]);
            if (out > max_val){
                max_val = out;
            }
        }
    }
    return max_val;
}


int main(){
    vector<int> w {12, 2, 1, 1, 4};
    vector<int> vals {4, 2, 1, 2, 10};
    int weight_lim = 6;

    int out = knapsack(vals, w, weight_lim);
    cout << out << endl;

    return 0;
}