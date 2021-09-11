#include <iostream>
#include <string>

using namespace std;

int main (){

    ios_base::sync_with_stdio(0);

    short t,sum;
    string s;
    cin >> t;
    while(t--){
        cin >> s;
        sum = 0;
        for(char &c : s)
            sum += c-'0';
        cout << sum << "\n";
    }

    return 0;
}