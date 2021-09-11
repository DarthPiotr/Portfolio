#include <iostream>
#include <cmath>

using namespace std;

int n, len;
int tab[999999];

int remove(int begin, int end, int cost) {
    int mincost = cost;
    for (int i = 1; i < end-begin; i += 2) {
        if (
            tab[begin + i - 1] - (begin >= 2 ? tab[begin - 2] : 0) >= 0 &&
            tab[end] - tab[begin + i - 1] >= 0
            ) {
            mincost = min(mincost, min(
                remove(begin, begin + i - 1, cost - tab[begin + i]),
                remove(begin + i + 1, end, cost - tab[begin + i])
            ));
        }
    }
    return mincost;
}

int main() {
    int i, tmp, cnt, cost;
    ios_base::sync_with_stdio(0);
    cin >> n;

    cnt = 0;
    len = 0;
    cost = n-1;
    for (i = 0; i < n; i++) {
        cin >> tmp;
        if (tmp == 0)
            cnt++;
        else {
            if (i > 0) {
                cnt++;
                tab[len++] = cnt;
            }
            tab[len] = (len >= 2 ? tab[len-2] : 0) + tmp;
            len++;
            cnt = 0;
        }
    }
    if(tab[len-1] < 0)
        cout << "-1\n";
    else
        cout << remove(0, len-1, n-1) << "\n";

    return 0;
}