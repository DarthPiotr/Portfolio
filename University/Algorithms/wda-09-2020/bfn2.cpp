#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

#define MAX 2147483647ULL
#define MAXROOT 46341
#define PRIMES 4792

using namespace std;

int primes[PRIMES];
bool part[500001];
int plen = 0;

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

void sieve() {
    bool tab[MAXROOT + 1] = {0};
    int len = 0, i, j;

    for (i = 2; i <= MAXROOT; i++) {
        if (!tab[i]) {
            primes[len++] = i;
            for (j = 2 * i; j <= MAXROOT; j += i) {
                tab[j] = 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int i, j;
    short t;
    int l, u, lim, pend;

    // przygotuj liczby pierwsze az do pierwiastka z maxa
    sieve();

    //t = 1;
    cin >> t;
    while (t--) {
        
        //l = 46342, u = 1046342;
        //l = 140, u = 150;
        cin >> l >> u;

        // jesli zaczyna sie w policzonych
        if (l < MAXROOT) {
            for (i = 0; primes[i] <= u && i < PRIMES; i++)
                if (primes[i] >= l) cout << primes[i] << "\n";

            if (u < MAXROOT) continue;
            l = MAXROOT + 2;
        }
        // jesli trzeba policzyc dla nowych liczb
        // jesli nie, to upewnij sie ze l jest nieparzyste
        else if (l % 2 == 0) l++;
        // upewnij sie ze u jest nieparzyste
        if (u % 2 == 0) u--;

        // ile bedzie sprawdzanych liczb
        lim = (u - l) / 2 + 1;
        memset(part, true, lim);

        // jaka bedzie ostatnia liczba pierwsza
        pend = sqrt(u);

        //for (k = 0; k < lim; k++) {// liczba ma wartosc l+k
        //    num = l + k;

            // jesli myslimy ze nie jest zlozona
            //if (part[k]) {
                
            
            // sprawdzamy dla kazdej znanej liczby pierwszej,
                // mniejszej od pierwiastka konca przedzialu
                for (i = 1; i < PRIMES && primes[i] <= pend; i++) {

                    // pierwsza liczba zlozonej z dana licza pierwsza to
                    j = (l / primes[i]) * primes[i];
                    // w razie gdyby bylo mniejsze niz l to znowu trzeba dodac
                    if (j < l) j += primes[i];
                    // jesli teraz jest parzyste to trzeba dodac zeby bylo nieparzyste
                    if (j % 2 == 0) j += primes[i];
                    
                    // jej indeks to 
                    j = (j-l)/2;
                    // (num / primes[i]) * primes[i] ((+ primes[i])) - l

                    for (; j < lim; j += primes[i]) {
                        part[j] = false;
                    }


               // }

          /*      if (part[k]) // jesli nadal nie jest zlozona to pokazac
                    //cout << num << "\n";
                    printf("%i\n", num);
            }*/
        }

                for (i = 0; i < lim; i++) {
                    if (part[i])
                        cout << l+2*i << "\n";
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