#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int n;
string s1,s2;
string s1p, s1n, s2p, s2n;

int main (){

    ios_base::sync_with_stdio(0);
    cin >> n >> s1 >> s2;

    s1p = s2p = s1n = s2n = "";
    for(int i = 0; i < n; i++){
        if(i%2){
            s1p += s1[i];
            s2p += s2[i];
        }
        else {
            s1n += s1[i];
            s2n += s2[i];
        }
    }
    sort(s1p.begin(), s1p.end());
    sort(s2p.begin(), s2p.end());
    sort(s1n.begin(), s1n.end());
    sort(s2n.begin(), s2n.end());

    if (s1p == s2p && s1n == s2n) cout << "TAK\n";
    else cout << "NIE\n";

    return 0;
}