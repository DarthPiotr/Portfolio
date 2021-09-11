#include <iostream>
#include <iomanip>

using namespace std;

int num(int n){
    
    int n1 = n;
    int cnt = 0;
    
    for(int i = 2; i < n; i++){
        if(n1 % i == 0)
            cnt++;

        while (n1 % i == 0){
            n1 /= i;
        }
    }

    return cnt;
}

int main (){

    ios_base::sync_with_stdio(0);

    for (int i = 30, j = 1; j <= 1000; i++){
        if(num(i) >= 3)
        cout << "["<< setw(4) <<j++<<"] "<< setw(4) << i << "\n";
    }

    return 0;
}