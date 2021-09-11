#include <iostream>

using namespace std;

int branch[1001], branchtmp[1001], sum[1000] = { 0 };
short n, k, q;

int main() {

    short i, j;
    ios_base::sync_with_stdio(0);
    cin >> n >> k >> q;

    for (i = 0; i < n; i++) {
        for (j = 0; j <= k; j++) {
            if (i == 0)
                branchtmp[j] = 1;
            else {
                branchtmp[j] =
                    ((j > 0 ? branch[j - 1] : 0) +
                    branch[j] +
                    (j < k ? branch[j + 1] : 0))%q;
            }
            sum[i] = (branchtmp[j] + sum[i])%q;
        }
        copy(branchtmp, branchtmp + k + 1, branch);
    }

    while (n--) {
        cin >> k;
        cout << sum[k - 1] << " ";
    }

    return 0;
}