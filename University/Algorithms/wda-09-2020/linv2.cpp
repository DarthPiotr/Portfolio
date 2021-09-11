#include <iostream>
#include <map>

using namespace std;

map<double, bool> tab;
struct point {
    short x, y;
} pts[200];
short len;

double geta(const point& p1, const point& p2) {
    if (p1.x == p2.x) return 69420;
    return (double)(p1.y - p2.y) / (p1.x - p2.x);
}

int main() {
    ios_base::sync_with_stdio(0);

    int n, i, cnt;
    double a;

    while (cin >> n) {
        if(n == 0) break;
        tab.clear();
        len = 0;
        cnt = 0;
        while (n--) {
            cin >> pts[len].x >> pts[len].y;

            for (i = 0; i < len; i++) {
                a = geta(pts[len], pts[i]);
                if (!tab[a]) {
                    tab[a] = true;
                    cnt++;
                }
            }
            len++;
        }
        cout << cnt << "\n";
    }

    return 0;
}