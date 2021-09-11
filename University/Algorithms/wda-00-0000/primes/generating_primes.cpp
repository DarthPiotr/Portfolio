#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>

#define SIZE 1000
#define FILE1 "primes_erato.txt"
#define FILE2 "primes_const.txt"

using namespace std;

ofstream file1, file2;

long double constant = 0;
vector<int> legit_primes;
vector<long double> approx;

void primes_erato() {
    const int size = SIZE - 2;
    bool tab[size];
    memset(tab, true, size);

    unsigned long long i, j;
    for (i = 0; i * i < size; i++) {
        if (tab[i]) {
            for (j = i + i + 2; j < size; j += i + 2)
                tab[j] = false;
        }
    }

    unsigned long long den = 1;
    int cnt = 1;
    for (i = 0; i < size; i++) {
        if (tab[i]) {
            file1 << i + 2 << "\n";
            legit_primes.push_back(i + 2);

            constant += (long double)(i + 1) / den;

            if (approx.size() == 0 || (approx.size() > 0 && approx[approx.size() - 1] != constant))
                approx.push_back(constant);

            den *= (i + 2);

            cout << cnt++ << ": " << i + 2 << " -> " << setprecision(300) << constant << "\n";
        }
    }
}

void primes_const() {
    const long double num = 2.920050977316134712092562917112019468002727899321426719772682533107733772127766124190178112317583742298338859553101376479;//2.920050977316;
    long double curr = num;

    while (curr <= SIZE) {
        file2 << (int)curr << "\n";

        curr = ((int)curr) * (curr - ((int)curr) + 1);
    }
}

void best_approx() {
    long double best = approx[0];
    int max = 0;

    int asize = approx.size();
    int cnt;
    for (int i = 0; i < asize; i++) {

        long double curr = approx[i];
        cnt = 0;
        while ((int)curr == legit_primes[cnt++]) {
            curr = ((int)curr) * (curr - ((int)curr) + 1);
        }

        if (cnt - 2 > max) {
            max = cnt - 2;
            best = approx[i];
        }
    }

    cout << "---------------------\n\nBest approx: " << setprecision(300) << best << "\nN-th prime: " << max + 1 << " (" << legit_primes[max] << ")\n";
}

int main() {

    ios_base::sync_with_stdio(0);

    //cout << numeric_limits<double>::max() << " " << numeric_limits<long double>::max() ;

    file1.open(FILE1);
    file2.open(FILE2);
    primes_erato();
    primes_const();
    file1.close();
    file2.close();

    best_approx();

    return 0;
}