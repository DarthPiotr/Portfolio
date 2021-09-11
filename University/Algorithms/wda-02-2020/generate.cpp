#include <iostream>

using namespace std;

int main(){
    int k = 1000000000;
    for(int i = 0; i < 100000; i++){
        cout << k-- << "\n";
    }
    return 0;
}