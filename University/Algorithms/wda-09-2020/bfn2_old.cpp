#include <iostream>

#define INTSIZE (sizeof(int)*8) // 32
#define MAX 2147483647

using namespace std;

int tab[(MAX/INTSIZE)/2 +1] = { 0 }; // 67108864

int nti(int n) { // number to index
    return (n - 1) / 2;
}

int main() {

    ios_base::sync_with_stdio(0);

    int count = 1;
    long long  i, j, ix, jx;
    for (i = 3; i <= MAX; i += 2) {
        ix = nti(i);
        if (!(tab[ix / INTSIZE] & (1 << ix % INTSIZE))) {
            count++;
            for (j = 3*i; j <= MAX; j += 2*i) {
                jx = nti(j);
                tab[jx / INTSIZE] |= (1 << jx % INTSIZE);
            }
        }
    }
    cout << count << "\n";

    return 0;
}