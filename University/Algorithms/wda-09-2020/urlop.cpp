#include <iostream>

using namespace std;

int main (){

    ios_base::sync_with_stdio(0);
    int n, longest=0, current=0;
    char c;

    cin >> n;
    while(n--){
        cin >> c;
        if(c == 'S') current++;
        else {
            if(current > longest) longest = current;
            current = 0;
        }
    }
    if(current > longest) longest = current;

    cout << longest << "\n";

    return 0;
}