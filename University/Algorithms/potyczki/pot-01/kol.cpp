#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct iv {
    int begin, end;
    short col;
} tab[1000000];
int n, m;

int main() {

    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    int i, num = 0;
    for (i = 0; i < m; i++) {
        cin >> tab[i].begin >> tab[i].end >> tab[i].col;
    }
    sort(
        tab,
        tab + m,
        [](const iv& a, const iv& b) -> bool { return a.begin < b.begin; });

    int yend, bend, beg, bprev = 0;
    beg = yend = bend = 0;
    for (i = 0; i < m; i++) {

        if (yend != 0 && bend != 0 && tab[i].begin > bprev)
            num += max(
                0,
                min(
                    tab[i].begin - 1,
                    min(yend, bend)
                ) - beg + 1
            );
        beg = max(tab[i].begin, beg);
        switch (tab[i].col) {
        case 1: // y
            yend = max(tab[i].end, yend);
            break;
        case 2: // b
            bend = max(tab[i].end, bend);
            break;
        case 3: // r
            beg = max(tab[i].end + 1, beg);
            break;
        }

        bprev = tab[i].begin;
    }

    if (yend != 0 && bend != 0)
        num += max(
            0,
            min(
                n,
                min(yend, bend)
            ) - beg + 1
        );

    cout << num;

    return 0;
}