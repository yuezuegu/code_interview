#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main(){
    string str1 = "abcs";
    string str2 = "cxzca";

    unordered_set<char> char_exists1{};
    unordered_set<char> char_exists2{};

    for(char c : str1){
        char_exists1.insert(c);
    }

    for(char c : str2){
        char_exists2.insert(c);
    }

    string out_str{};

    for(char c : str1){
        if(char_exists2.count(c) == 0){
            out_str = out_str + c;
        }
    }

    for(char c : str2){
        if(char_exists1.count(c) == 0){
            out_str = out_str + c;
        }
    }

    cout << "Out: " << out_str << endl;

    return 0;
}