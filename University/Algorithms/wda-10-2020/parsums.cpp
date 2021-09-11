#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

short tab[1000000];
int len;

int main() {

    ios_base::sync_with_stdio(0);

    int n, i, j;
    int res, last, revi=INT_MAX;
    for (;;) {
        cin >> n;
        if (!n) break;
        len = 0;
        res = n;
        last = -1;
        for (i = 0; i < n; i++) {
            cin >> tab[len++];
            if (tab[i] < 0) {
                if (i > 0)
                    tab[i] += tab[i - 1];

                for (j = i-1; j >= last; j--) {
                    cerr << "Checking (" << j + 1 << ", " << i << ")\n";
                    if (tab[i] - (j < 0 ? 0 : tab[j]) < 0) {
                        res--;
                        cerr << "Cannot start with k: " << j+1 << "\n";
                    }
                    else break;
                }
                // jesli cofnelismy sie bardziej niz dotychczas
                if (j+1 < revi) revi = max(j, -1);
                // jesli chcemmy sprawdzic czy na pewno jest ok i cofamy dalej
                else {
                    for (; revi >= 0; revi--) {
                        cerr << "Checking (" << revi + 1 << ", " << i << ")\n";
                        if (tab[i] - (revi < 0 ? 0 : tab[revi]) < 0) {
                            res--;
                            cerr << "Cannot start with k: " << revi + 1 << "\n";
                        }
                        else break;
                    }
                }
                last = i;
            }
            else if (i > 0) {
                tab[i] += tab[i - 1];
            }
        }
        cout << res << "\n";
        cerr << "---\n";
    }

    return 0;
}