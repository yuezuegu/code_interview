

#include <iostream>

using namespace std;

int solution_cnt = 0;

int steps(int remaining_stairs, int no_steps){
    if(no_steps == 0){
        if(remaining_stairs == 0){ return ++solution_cnt; }
        else { return solution_cnt;}
    }
    else{
        steps(remaining_stairs-1, no_steps-1);
        steps(remaining_stairs-2, no_steps-1);
        steps(remaining_stairs-3, no_steps-1);
        return solution_cnt;
    }
}

int main(){
    int stairs = 4;
    int no_steps = 2;
    
    steps(stairs, no_steps);
    cout << solution_cnt << endl;

    return 0;
}