#include <iostream>
#include <string>

using namespace std;

int main(){

    ios_base::sync_with_stdio(false);

    int n, t;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> t;
        cout << (t % 2 ? "Sorry" : "Thankyou") << " Shaktiman\n";
    }

    return 0;
}