#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

// exponent of base
#define BASEEXP 9 //9
// must be 10^BASEEXP
#define BASE 100000000  // 1000000000
// Must be int
#define SIZE 100

class bigint {
public:
    bigint() {}
    bigint(const int& n) { saveInt(n); }
    bigint(const string& s) { saveString(s); }

    void operator= (const int& n) { saveInt(n); }
    void operator= (const string& s) { saveString(s); }
    void operator= (const char c[]) {
        saveString(string(c));
    }

    bigint operator+ (const bigint& bn) {
        bigint res = 0; int carry = 0;
        for (int i = 0; i < SIZE; i++) {
            res.number[i] = this->number[i] + bn.number[i] + carry;
            carry = res.number[i] / BASE;
            res.number[i] %= BASE;
        }
        return res;
    }

    bigint operator-(const bigint &bn){
        bigint res = 0;
        bigint sub;
        copy(this->number, this->number+SIZE, sub.number);

        for(int i = 0, j; i < SIZE; i++){
            res.number[i] = sub.number[i] - bn.number[i];
            if(res.number[i] < 0){
                res.number[i] += BASE;
                for(j = i+1; j < SIZE; j++){
                    if(sub.number[j] == 0) sub.number[j] = BASE-1;
                    else { 
                        sub.number[j]--;
                        break;
                    }
                }
            }
        }

        return res;
    }

    bigint operator* (const bigint& bn) {
        bigint res = 0, tmp;
        int carry = 0;
        long long product;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                tmp = 0;
                product = (long long)this->number[j] * bn.number[i];

                if (i + j < SIZE) {
                    tmp.number[i + j] += product % BASE;
                    if (i + j + 1 < SIZE) tmp.number[i + j + 1] += product / BASE;
                }
                res = res + tmp;
            }
        }
        return res;
    }

    string str() {
        stringstream s;
        bool write = false;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (write) {
                s << setfill('0') << setw(BASEEXP) << number[i];
            }
            else if (number[i] != 0) {
                write = 1;
                s << number[i];
            }
        }
        return s.str();
    }

    void debug() {
        cerr << "[DEBUG]: Value in table: \n";
        for (int i = SIZE - 1; i >= 0; i--) {
            cerr << setfill(' ') << "[" << setw(2) << i << "]: " << setfill('0') << setw(BASEEXP) << number[i] << "\n";
        }
        cerr << "---\n\n";
    }
private:
    int number[SIZE] = { 0 };

    void saveInt(int n) {
        memset(number, 0, SIZE*sizeof(number[0]));
        if (n < BASE)
            number[0] = n;
        else
            saveString(to_string(n));

    }
    void saveString(string s) {
        memset(number, 0, SIZE);
        int base = 1, len = s.size();
        for (int i = 0; i < len; i++) {
            if (i % BASEEXP == 0) base = 1;
            number[i / BASEEXP] += base * (s[len - i - 1] - '0');
            base *= 10;
        }
    }
};

int main() {

    ios_base::sync_with_stdio(0);

    bigint a ("124135171365166513663167316731658136");    
    bigint b ("1");
    bigint c = a*b;

    cout << c.str() << "\n";

    return 0;
}