#include <stdio.h>
#include <stdlib.h>

int bin_to_int(char* bin){
    int ind = 0;
    char c = bin[0];

    int out = 0;

    while (1){
        if (c == '1'){
            out++;
        }

        c = bin[++ind];

        if(c == '\0'){
            return out;
        }
        else{
            out *= 2;
        }
    }
}

char* int_to_bin(int num){
    char* out = (char*)malloc(33 * sizeof(char));
    out[32] = '\0';

    for(int i = 0; i < 32; i++){
        out[31-i] = (num % 2) + '0';
        num = num / 2;
    }
    return out;
}

int solution(int N, int M, unsigned i, unsigned j){
    int len = j - i + 1;
    int mask = ( (1 << len) - 1) << i;

    //printf("%i \n", ~(mask));

    N = N & ~mask;
    //printf("%s \n", int_to_bin(N));

    return N | (M << i);
}

int main(){

    char N_str[] = "10000010001";
    char M_str[] = "10011";
    int i = 2;
    int j = 6;

    int out = solution(bin_to_int(N_str), bin_to_int(M_str), i, j);
    printf("%s \n", int_to_bin(out));

    return 0;
}

