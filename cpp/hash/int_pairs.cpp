#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

vector<pair<int,int>> find_pairs(vector<int> &vec, int sum){
    vector<pair<int,int>> out_pairs {};

    map<int, int> num_cnt {};

    for (int v : vec){
        if(num_cnt.count(v) == 0){
            num_cnt.insert({v, 1});
        }
        else{
            num_cnt[v]++;
        }

        int pair_val = sum - v;
        if(num_cnt.count(pair_val) > 0){
            if(num_cnt[pair_val] > 0){
                out_pairs.push_back({v, pair_val});
                num_cnt[v]--;
                num_cnt[pair_val]--;
            }
        }
    }
    return out_pairs;
}


int main(){
    vector<int> vec {0, 3, 5, 2, 1, 7, 4, 2, 3, 5, 6, 0, -1, 4, 8};
    int sum = 7;

    auto out = find_pairs(vec, sum);

    for (auto p : out){
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}