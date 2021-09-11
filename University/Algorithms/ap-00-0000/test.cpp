#include <iostream>
#include <cstring>

#define SIZE 3
using namespace std;

typedef unsigned int T;

int main (){

    T tab[SIZE];

    memset(tab, 0b01010101, sizeof(tab));
    for(auto &e : tab) cout << e << " ";
    cout << "\n";

    for(int i = 0; i < SIZE*sizeof(T)*8; ++i){
        cout << ((tab[i/(8*sizeof(T))] & (1 << (7 - (i%8)))) >> (7 - (i%8)));
        if(i % (8*sizeof(T)) == 8*sizeof(T)-1) cout << " | ";
    }
    cout << "\n";

    return 0;
}