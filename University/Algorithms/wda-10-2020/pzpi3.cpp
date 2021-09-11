#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Kwadraty liczb pierwszych!
/*
void generate(){
    int i, j;
    double sum, cnt;
    for (i = 1; i <= 10000; i++) {
        sum = cnt = 0;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                sum += j;
                cnt++;
                if (j * j != i) {
                    sum += i / j;
                    cnt++;
                }
            }
        }
        if (cnt > 0 && sum / cnt <= sqrt(i))
            cout << i << "\n";
    }
}*/

bool sieve[40000] = { 0 };
int tab[4203];
int len = 0;

int searchLower(int beg, int end, int value) {
    if (beg == end) return end;
    
    int mid = (beg + end) / 2;

    if (tab[mid] < value) return searchLower(mid + 1, end, value);

    if (mid - 1 >= 0) {
        if (tab[mid - 1] >= value) return searchLower(beg, mid - 1, value);
        return mid;
    }
    return 0;
}

int searchUpper(int beg, int end, int value) {
    if (beg == end) return beg;
    
    int mid = (beg + end) / 2;

    if (tab[mid] > value) return searchUpper(beg, mid-1, value);

    if (mid + 1 < len) {
        if (tab[mid + 1] <= value) return searchUpper(mid+1, end, value);
        return mid;
    }
    return len-1;
}

int main() {

    ios_base::sync_with_stdio(0);

    int i, j, n;
    // prepare the numbers
    for (i = 2; i < 40000; i++) {
        if (!sieve[i]) {
            tab[len++] = i * i;
            for (j = i + i; j < 40000; j += i) {
                sieve[j] = 1;
            }
        }
    }
    cin >> n;
    while(n--){
        cin >> i >> j;
        cerr << "i: " << searchLower(0, len-1, i) << ", j: " << searchUpper(0, len - 1, j) << "\n";
        if(j < tab[0] || i > tab[len-1]) cout << "0\n";
        else cout << searchUpper(0, len - 1, j) - searchLower(0, len-1, i) + 1 << "\n";
    }
        
    return 0;
}