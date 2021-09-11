#include <iostream>
#include <cmath>
#include <vector>

#define MAX 2147483647ULL
#define MAXROOT 46341
#define PRIMES 4792

using namespace std;

int primes[PRIMES];
int len = 0;
bool tab[MAXROOT + 1] = { 0 };

int binSearch(int val, int l, int r) {


    int mid = (r + l) / 2;
    if (primes[mid] <= val) {
        if (mid + 1 < PRIMES && val < primes[mid + 1])
            return mid;
        if (mid + 1 >= PRIMES)
            return mid;
    }
    if (l == r) return -1;

    if (primes[mid] < val) return binSearch(val, mid + 1, r);

    return binSearch(val, l, mid);
}

int main() {
    ios_base::sync_with_stdio(0);
    int i, j;
    for (i = 2; i <= MAXROOT; i++) {
        if (!tab[i]) {
            primes[len++] = i;
            for (j = 2 * i; j <= MAXROOT; j += i) {
                tab[j] = 1;
            }
        }
    }

    short t;
    int l, u, maxindex;
    bool prime;
    cin >> t;
    while (t--) {
        cin >> l >> u;

        if (u < MAXROOT) {
            for (i = 0; primes[i] <= u; i++)
                if (primes[i] >= l) cout << primes[i] << "\n";
        }
        else {
            //cout << "MAXINDEX: " << maxindex << "(" << primes[maxindex] << ")" << "\n";
            for (; l <= u; l++) {
                prime = true;
                maxindex = binSearch(sqrt(l) + 1, 0, PRIMES - 1);
                for (i = 0; i <= maxindex; i++) {
                    if (l != primes[i] && l % primes[i] == 0) {
                        prime = false;
                        break;
                    }
                }
                if (prime)
                    cout << l << "\n";
            }
        }
    }

    /*int curr;
    for(int i = 2; i <= MAX; i++){
        curr = binSearch(i, 0, PRIMES-1);
        cout << "The best value for " << i << " is " << primes[curr] << "\n";

        if(i == 100)
        i = MAX-10;
    }*/

    return 0;
}