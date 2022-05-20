

#include <iostream>
#include <vector>

using namespace std;


class BitVector{
private:
    int no_bits;
    int* bitvec;

public:
    BitVector(int no_bits){
        this->no_bits = no_bits;
        this->bitvec = new int[no_bits/sizeof(int)] {0};
    }

    ~BitVector(){
        delete [] bitvec;
    }

    bool check_bit(int bit_ind){
        if (bit_ind >= this->no_bits)
            throw 0;
        int word = this->bitvec[bit_ind/sizeof(int)];
        return word >> (bit_ind%sizeof(int)) % 2;
    }

    void set_bit(int bit_ind){
        if (bit_ind >= this->no_bits)
            throw 0;
        this->bitvec[bit_ind/sizeof(int)] |= ( 1 << (bit_ind%sizeof(int)) );
    }
};

int main(){
    BitVector bitVector (64);

    cout << bitVector.check_bit(33) << endl;
    bitVector.set_bit(33);

    try{
        cout << bitVector.check_bit(64) << endl;
    }
    catch(int &ex){
        cerr << "Index out of range" << endl;
    }

    return 0;
}