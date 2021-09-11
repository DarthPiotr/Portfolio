#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

typedef long double ld;

#define INTSIZE (sizeof(int)*8) // 32
#define MAX 16008000

struct point {
    short x, y;
} pts[200];
short len = 0;

unsigned int tab[(MAX / INTSIZE) + 1] = { 0 };

bool read(int k) {
    //cerr << "READING: " << k << "(" << k / INTSIZE << " + " << k % INTSIZE << ")" << "\n";
    return tab[k / INTSIZE] & (1 << (k % INTSIZE));
}
void set(int k) {
    //cout << "SETTING: " << k << "(" << k / INTSIZE << " + " << k % INTSIZE << ")" << "\n";
    tab[k / INTSIZE] |= (1 << (k % INTSIZE));
}

int nwd(int a, int b) {
    int tmp;
    while (b != 0) {
        tmp = a;
        a = b;
        b = tmp % b;
    }
    return a == 0 ? 1 : a;
}

int Hash(int x1, int y1, int x2, int y2) {
    if (y1 == y2) return 8004001;
    int num = y1 - y2;
    int den = x1 - x2;
    if (num < 0) {
        num = -num;
        den = -den;
    }
    int gcd = nwd(abs(num), abs(den));

    return 4001 * (num / gcd + 2000) + (den / gcd + 2000);
}

int main() {
    ios_base::sync_with_stdio(0);

    cerr << "Table initialized as " << (MAX / INTSIZE) + 1 << "\n";
    /*cerr << geta(1,1,333,106) << " " << geta(4,2,1,1) << "\n";
    cerr << geta(-4,1,-1,2) << " " << geta(-1,2,-4,1) << "\n";
    cerr << geta(1,-2,4,-1) << " " << geta(4,-1,1,-2) << "\n";
    cerr << geta(-4,-2,-1,-1) << " " << geta(-1,-1,-4,-2) << "\n";
    cerr << geta(-5,-3,5,3) << " " << geta(2,1,-2,-1) << "\n";*/

    int n, i, cnt = 0, h;
    while (cin >> n) {

        cnt = 0;
        len = 0;
        memset(tab, 0, sizeof(tab));

        while (n--) {
            cin >> pts[len].x >> pts[len].y;

            for (i = 0; i < len; i++) {
                h = Hash(pts[len].x, pts[len].y, pts[i].x, pts[i].y);
                if (!read(h)) { // wasnt already
                    cnt++;
                    set(h);
                    //cerr << "Connection between: " << len << " and " << i << "\n";
                }
            }
            len++;
        }
        cin >> n;

        cout << cnt << "\n";
    }

    return 0;
}