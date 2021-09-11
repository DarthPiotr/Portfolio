#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

// factorial
#define TABSIZE 101
// BIG INT
#define BASE 1000000000
#define BASEEXP 9
#define SIZE 24

using namespace std;

typedef long long ll;
typedef int base_type;

// dla liczb calk. <0, 10^200>
class big {
public:
    base_type val[SIZE] = { 0 };

    big() {}
    big(string number) {
        short index,  len = number.size();
        base_type b = 1;
        for (short i = 0; i < len; i++) {
            index = i / BASEEXP;
            if (i % BASEEXP == 0) b = 1;
            val[index] += b * (number[len - i - 1] - '0');
            b *= 10;
        }
    }

    big operator+ (const big& a) {
        big result;
        base_type carry = 0, tmp;
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

    big operator/ (const int &a){
        big result;
        base_type carry = 0;
        for(short i = SIZE-1; i >= 0; i--){
            result.val[i] = (carry*BASE + this->val[i])/a;
            carry = (carry*BASE + this->val[i])%a;
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

};

int main(){
    ios_base::sync_with_stdio(0);
    string together, difference;
    big diff, tog;
    while(cin >> together){
        cin >> difference;
        tog = big(together);
        diff = big(difference);
        
        tog = (tog-diff)/2;
        cout << (diff+tog).str() << "\n" << tog.str() << "\n";
    }
    return 0;
}