#include <iostream>

using namespace std;

int NWD(int a, int b){
    int c;
    while(b){
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);

    int a, b, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        cout << NWD(a, b) << "\n";
    }

    return 0;
}