#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

#define MODULO 1000000007

using namespace std;

typedef long long ll;

short n;
int tab[5000];
int sums[25000001] = { 0 };

int main() {

    ios_base::sync_with_stdio(0);
    short i, s, last = 0;
    int sum = 0;
    ll poss = 0;

    cin >> n;
    for (i = 0; i < n;)
        cin >> tab[i++];
    sort(tab, tab + n);

    if (tab[0] == 1) {

        sum = 0;
        sums[0] = 1;
        poss = 0;
        for (i = 0; i < n; i++) {
            if (tab[i] > sum + 1)
                break;

            for (s = sum; s >= tab[i]-1; s--) {
                if (sums[s] > 0) {
                    sums[s + tab[i]] += sums[s];
                    sum = max(sum, s + tab[i]);
                    poss += sums[s];
                    poss %= MODULO;
                }
            }
        }

        cout << poss << "\n";
    }
    else
        cout << "0\n";

    return 0;
}