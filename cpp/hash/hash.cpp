
#include <iostream>
#include <map>
#include <string>
#include <numeric>
#include <utility>

using namespace std;


void solution(string &str){
    map<char, int> char_cnt;

    for (string::iterator it = str.begin(); it != str.end(); it++){
        auto key = char_cnt.find(*it);
        if (key == char_cnt.end()){
            char_cnt.insert({*it, 1});
        }
        else{
            char_cnt[*it]++;
        }
    }

    int max_cnt = 0;
    char max_char;
    for(auto it = char_cnt.begin(); it != char_cnt.end(); it++){
        if (it->second > max_cnt){
            max_cnt = it->second;
            max_char = it->first;
        }    
    }

    cout << max_char << " " << max_cnt << endl;
}



int main(){
    string str = "Pulkit is a dog!!!!!!!!!!!!";
    solution(str);

    return 0;
}