#include <iostream>
#include <string>

using namespace std;

string remove_duplicate(string str, char last_char){
    if (str.empty()){
        return "";
    }
    if(last_char == '\0'){
        return remove_duplicate( str.substr(1, str.size()), str[0]);
    }
    else{
        if(last_char != str[0]){
            string out_str {last_char};
            return out_str + str.substr(0,1) + remove_duplicate( str.substr(1, str.size()), str[0]);
        }
        else{
            return remove_duplicate( str.substr(1, str.size()), str[0]);
        }
    }
}

int main(){
    string str = "geeksforgeek";

    str = remove_duplicate(str, '\0');

    cout << str << endl;

    return 0;
}