#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

typedef long double ld;
typedef long long ll;

#define INTSIZE (sizeof(unsigned int)*8) // 32
#define MAX 16008000LL

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
ll Hash(int x1, int y1, int x2, int y2) {
    if (y1 == y2) return 8004001;
    ll num = y1 - y2;
    ll den = x1 - x2;
    if (num < 0) {
        num *= -1;
        den *= -1;
    }
    int gcd = nwd(abs(num), abs(den));

    return 4001 * (num / gcd + 2000) + (den / gcd + 2000);
}

int rrand(int min, int max){
    return min + rand()%(max-min+1);
}

int main(){
    srand(time(NULL));
    //ios_base::sync_with_stdio(0);

    ll i, j, k, l, max = -1, h;
    ll size = (MAX / INTSIZE) + 1;

    //Hash(0,0,1000,1000);

    for(;;){
        i = rrand(-1000, 1000);
        j = rrand(-1000, 1000);
        k = rrand(-1000, 1000);
        l = rrand(-1000, 1000);
        h = Hash(i,j,k,l);

        try{
            read(h);
        }
        catch (const std::exception& e) {
            cerr << h << " cannot be accessed (" << i << " " << j << " " << k << " " << l << "\n";
            break;
        }
    }

    return 0;
}