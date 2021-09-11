#include <iostream>
#include <cmath>

using namespace std;

int main(){

    for(int i = 0; i < 22; i ++){
        cout << 60*i + ceil(i*60.0/11) << ", ";
    }

    return 0;
}