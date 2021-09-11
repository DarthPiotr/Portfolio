#include <iostream>

using namespace std;

int T;

int main (){

    ios_base::sync_with_stdio(0);

    int num, sum, i;

    cin >> T;
    while(T--){
        cin >> num;
        sum = 0;
        for (i = 5; i <= num; i *=5)
            sum += num/i;
        cout << sum << '\n';
    }

    return 0;
}