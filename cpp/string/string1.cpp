#include <iostream>
#include <string>

using namespace std;


int count_spaces(string &str, unsigned L){
    string::iterator curr = str.begin();

    int cnt = 0;
    while (curr - str.begin() < L){
        if (*curr == ' '){
            cnt++;
        }
        curr++;
    }
    return cnt;
}

void solution(string &str, unsigned L){

    int no_spaces = count_spaces(str, L);

    string::iterator dest = str.begin()+L+2*no_spaces-1;
    string::iterator curr = str.begin()+L-1;

    while (curr >= str.begin()){
        if (*curr == ' '){
            *dest = '0'; dest--;
            *dest = '2'; dest--;
            *dest = '%'; dest--;
            curr--;
        }
        else{
            *dest = *curr;
            dest--;
            curr--;
        }
    }
}

int main(){

    string str = "Mr John Smith        ";
    unsigned L = 13;

    solution(str, L);

    cout << str << endl;

    return 0;
}