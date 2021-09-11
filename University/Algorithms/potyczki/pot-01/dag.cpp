#include <iostream>

using namespace std;

short indexes[44];
short len;
int k;
int fib[44];

int main() {

    ios_base::sync_with_stdio(0);
    int i, n;
    fib[0] = fib[1] = 1;
    for (i = 2; i < 44; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    cin >> k;
    len = 0; n = 1;
    for (i = 43; k > 0 && i > 0; i--) {
        if (k >= fib[i]) {
            k -= fib[i];
            indexes[len++] = i;
            n += (n == 1 ? i : 1);
        }
    }

    cout << n << "\n";
    for (i = 1; i <= n; i++) {
        if (len > 1)
            cout << i + 1 << " " << n - indexes[--len] << "\n";
        else
            cout << (i + 1 > n ? -1 : i + 1) << " " << (i + 2 > n ? -1 : i + 2) << "\n";
    }

    return 0;
}