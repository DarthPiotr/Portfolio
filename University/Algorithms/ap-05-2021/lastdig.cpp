#include <iostream>

using namespace std;

//..0 -> 0
//..1 -> 1
//..2 -> 2 4 8 6
//..3 -> 3 9 7 1
//..4 -> 4 6
//..5 -> 5
//..6 -> 6
//..7 -> 7 9 3 1
//..8 -> 8 4 2 6
//..9 -> 9 1

int tab[] = {
    0, 0, 0, 0, // 0
    1, 1, 1, 1, // 1
    2, 4, 8, 6, // 2
    3, 9, 7, 1, // 3
    4, 6, 4, 6, // 4
    5, 5, 5, 5, // 5
    6, 6, 6, 6, // 6
    7, 9, 3, 1, // 7
    8, 4, 2, 6, // 8
    9, 1, 9, 1 }; // 9

int n;

int main (){

    ios_base::sync_with_stdio(0);
    int a, b;
    cin >> n;
    while(n--){
        cin >> a >> b;
        a %= 10;

        if(b == 0) cout << "1\n";
        else cout << tab[4*a  + (b-1)%4] << "\n";
    }

    return 0;
}