#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Map{
private:
    int w;
    int h;
    bool* map_array;
    int valid_path_cnt;

public:
    Map(int w, int h, vector<pair<int,int>> obstacles){
        this->w = w;
        this->h = h;
        this->valid_path_cnt = 0;
        map_array = new bool[w*h] {false};

        for (auto loc : obstacles){
            map_array[index(loc.first, loc.second)] = true;
        }
    }

    void increment_path_cnt(){this->valid_path_cnt++;}
    int get_path_cnt(){return this->valid_path_cnt;}

    int index(int x, int y){ return y*this->w+x;}

    bool check_obstacle(int x, int y){
        return map_array[index(x, y)];
    }

    bool has_reached_dest(int x, int y){
        return x == this->w - 1 && y == this->h - 1;
    }

    bool is_inside_map(int x, int y){
        return x < this->w && y < this->h;
    }

};




void path(pair<int, int> pos, Map &map){
    cout << pos.first << " " << pos.second << endl;
    if(map.has_reached_dest(pos.first, pos.second)){
        map.increment_path_cnt();
        cout << "Reached destination." << endl;
        return;
    }
    else if (map.check_obstacle(pos.first, pos.second)){
        return;
    }
    else{
        if (map.is_inside_map(pos.first+1, pos.second)){
            path({pos.first+1, pos.second}, map);
        }
        if (map.is_inside_map(pos.first, pos.second+1)){
            path({pos.first, pos.second+1}, map);
        }
    }
}

int main(){
    Map map (3, 3, {});

    path({0,0}, map);

    cout << map.get_path_cnt() << endl;

    return 0;
}