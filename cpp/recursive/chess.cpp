
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

/*
    Vector<pair<int, int>> -> queen_locs

    solution (queen_locs):
        if (queen_locs.size()==8):
            print_chess_board()

        for(i = 0:7):
            if(not check_hazard(i, queen_locs)):
                tmp_locs = queen_locs
                tmp_locs.push_back(queen_locs);
                solution (tmp_locs)
*/

int board_size = 8;

bool check_hazard(pair<int,int> new_loc, vector<pair<int,int>> &queen_locs){
    for (auto qloc : queen_locs){
        if (new_loc.second == qloc.second){
            // cout << "Column hazard: " <<  new_loc.second << " " << qloc.second << endl;
            return true;
        }
        if ( abs(new_loc.second - qloc.second) == abs(new_loc.first - qloc.first) ){
            // cout << "Diagonal hazard: " <<  new_loc.first << " " << new_loc.second << " " << qloc.first << " " << qloc.second << endl;
            return true;
        }
    }
    return false;
}

void print_chess_board(vector<pair<int,int>> &queen_locs){
    for (int i = 0; i < board_size; i++){
        cout << "---";
    }
    cout << endl;

    for(int r = 0; r < board_size; r++){
        auto qloc = queen_locs[r];
        for(int c = 0; c < board_size; c++){       
            if (c == qloc.second){
                cout << "|x";
            }
            else{
                cout << "| ";
            }
        } 
        cout << "|" << endl;
    }

    for (int i = 0; i < board_size; i++){
        cout << "---";
    }
    cout << endl;
    
}


void solution(int row, vector<pair<int,int>> &queen_locs){
    if (queen_locs.size()==board_size){
        print_chess_board(queen_locs);
        return;
    }

    for (int i = 0; i < board_size; i++){
        if(!check_hazard({row, i}, queen_locs)){
            queen_locs.push_back({row, i});
            solution(row+1, queen_locs);
            queen_locs.pop_back();
        }
    }



}






int main(){
    vector<pair<int,int>> queen_locs {};
    solution(0, queen_locs);

    return 0;
}