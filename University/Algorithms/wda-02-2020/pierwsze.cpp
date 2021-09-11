#include <iostream>

#define SIZE 10000

using namespace std;

bool tab[SIZE];

int main(){
    int i, j;
    for(i = 0; i < SIZE; i++){
        tab[i] = true;
    }

    tab[0] = false;

    for(i = 2; i -1 < SIZE; i++){
        if(tab[i-1]){
            for(j = i+i; j-1 < SIZE; j += i){
                tab[j-1] = false;
            }
        }
    }

    int n;
    short num;
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> num;
        cout << (tab[num-1] ? "TAK" : "NIE") << "\n";
    }

    return 0;
}