#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

int tab[1000000];
int minsRL[1000000];
int minsLR[1000000];

int main() {

    ios_base::sync_with_stdio(0);

    int n, i;
    int res;
    for (;;) {
        cin >> n;
        if (!n) break;
        res = n;
        for (i = 0; i < n; i++) {
            cin >> tab[i];

            if (i > 0){
                tab[i] += tab[i - 1];
                minsLR[i] = min(minsLR[i - 1], tab[i]);
            }
            else
                minsLR[i] = tab[i];
        }
        while (--i >= 0) {
            if (i < n - 1) {
                minsRL[i] = min(minsRL[i + 1], tab[i]);
            }
            else
                minsRL[i] = tab[i];
        }
        while (++i < n) {
            if (i > 0) {
                if (minsRL[i] - tab[i - 1] < 0 || minsLR[i-1] + tab[n-1]-tab[i-1] < 0) res--;
            }
            else if (tab[i] < 0 || minsLR[n-1] < 0) res--;
        }
        cout << res << "\n";
    }

    return 0;
}