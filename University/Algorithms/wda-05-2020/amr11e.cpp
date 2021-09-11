#include <iostream>

using namespace std;

short tab[1000];

short num(short n){
    
    short n1 = n;
    short cnt = 0;
    
    for(short i = 2; i < n && n1 > 1; i++){
        if(n1 % i == 0)
            cnt++;

        while (n1 % i == 0){
            n1 /= i;
        }
    }

    return cnt;
}

int main (){

    short t, n, i, j;
    ios_base::sync_with_stdio(0);

    // wygeneruj te liczby
    for (i = 30, j = 0; j < 1000; i++){
        if(num(i) >= 3)
            tab[j++] = i;
    }

    cin >> t;
    for (i = 0; i < t; i++){
        cin >> n;
        cout << tab[n-1] << "\n";
    }

    return 0;
}