#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

typedef long long ll;

#define BASE 1000000000000000000
#define BASEEXP 18
#define SIZE 12

// dla liczb calk. <0, 10^200>
class big {
public:
    ll val[SIZE] = { 0 };

    big() {}
    big(string number) {
        short index,  len = number.size();
        ll b = 1;
        for (short i = 0; i < len; i++) {
            index = i / BASEEXP;
            if (i % BASEEXP == 0) b = 1;
            val[index] += b * (number[len - i - 1] - '0');
            b *= 10;
        }
    }

    big operator+ (const big& a) {
        big result;
        ll carry = 0, tmp;
        for (short i = 0; i < SIZE; i++) {
            tmp = this->val[i] + a.val[i] + carry;
            result.val[i] = tmp % BASE;
            carry = tmp / BASE;
        }
        return result;
    }

    big operator- (const big &a){
        big result;
        copy(this->val, this->val+SIZE, result.val);
        for (short i = 0; i < SIZE; i++) {
            for(short j = i+1; result.val[i] < a.val[i]; j++){
                if(result.val[j] > 0){
                    result.val[j]--;
                    result.val[i] += BASE;
                }
                else
                    result.val[j] = BASE-1;
            }
            result.val[i] -= a.val[i];
        }
        return result;
    }

    string str() {
        stringstream ss;
        bool write = false;
        for (short i = SIZE - 1; i >= 0; --i) {
            if (write) {
                ss << setfill('0') << setw(BASEEXP) << val[i];
            }
            else if (val[i] > 0) {
                write = true;
                ss << val[i];
            }
        }
        return ss.str();
    }

}c, d;

int main() {
    ios_base::sync_with_stdio(0);
    string sbd, sc;
    short t;
    cin >> t;
    for(short a = 0; a < t; a++){
        //      b      c
        cin >> sbd >> sc;
        c = big(sc);
        d = big(sbd);
        c = c+c;
        c = c-d;
        //      d
        cin >> sbd;
        d = big(sbd);
        c = c-d;

        // 2c - b - d
        cout << c.str() << "\n";
    }

    return 0;
}