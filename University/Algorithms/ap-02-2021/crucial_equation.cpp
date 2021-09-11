#include <iostream>

using namespace std;

int gcd(int a, int b){
    int t;
    while(b != 0){
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main (){

    ios_base::sync_with_stdio(0);

    int n, a, b, c;
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a >> b >> c;
        cout << "Case " << i << ": ";
        if(c % gcd(a,b) == 0) cout << "Yes\n";
        else cout << "No\n";     
    }

    return 0;
}