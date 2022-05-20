#include <iostream>
#include <string>

using namespace std;


string solution(string &str){
    
    string::iterator src_it = str.begin();
    int out_len = 0;

    while (src_it != str.end()){
        char seq_key = *src_it;
        int seq_cnt = 0;

        while(*src_it==seq_key && src_it != str.end()){
            src_it++;
            seq_cnt++;
        }
        
        out_len++;
        out_len += to_string(seq_cnt).size();

        if(out_len > str.size()){
            return str;
        }
    }

    string out (out_len, '\0');

    src_it = str.begin();
    string::iterator dest_it = out.begin();

    while (src_it != str.end()){
        char seq_key = *src_it;
        int seq_cnt = 0;

        while(*src_it==seq_key && src_it != str.end()){
            src_it++;
            seq_cnt++;
        }

        *dest_it = seq_key; dest_it++;
        string num_str = to_string(seq_cnt);
        out.replace(dest_it, dest_it+num_str.size(), num_str);
        dest_it += num_str.size();
    }

    return out;
}



int main(){
    string str = "aabcaa"; 
    string out = solution(str);

    cout << out << endl;

    return 0;
}