#include <iostream>
#define OFFSET 1000000

using namespace std;

struct ln{
    int a = 0, b = 0;
} tab[2000001];

int main (){
    ios_base::sync_with_stdio(0);

    int t, a, b, i, n;
    cin >> n;
    for(i = 0; i < n; i++){
        cin >> t >> a >> b;
        if(t == 1)
            tab[a-b+OFFSET].a++;
        else
            tab[a-b+OFFSET].b++;
    }

    t = 0;
    for(i = 0; i < 2000001; i++){
        t += min(tab[i].a, tab[i].b);
    }

    cout << t;

    return 0;
}