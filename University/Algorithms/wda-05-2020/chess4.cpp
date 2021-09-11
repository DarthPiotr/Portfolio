#include <iostream>

using namespace std;
short t;
int m, n;

int main (){

    ios_base::sync_with_stdio(0);

    cin >> t;
    for(short i = 0; i < t; i++){
        cin >> m >> n;

        if(m%2) swap (m, n);

        if(m == 2 && n == 1){
            cout << "NO\n";
            continue;
        }
        bool test = !(m%2 || (n-1)%2);
        cout << ((test) ? "YES\n" : "NO\n");
    }

    return 0;
}