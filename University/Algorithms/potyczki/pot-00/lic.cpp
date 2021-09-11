// C++ program to Find the number
// of numbers in a range that are
// divisible by exactly K of it's
// digits
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int LCM = 2520;
const int MAXDIG = 10;
 
// To store the results for
// overlapping subproblems
int memo[MAXDIG][2][LCM][(1 << 9) + 5];
 
// To store the digits of the
// given number
vector<int> dig;
int K;
 
// Function to update the dp
// table
int dp(int index, int tight,
       int rem, int mask)
{
 
    // To find the result
    int& res = memo[index][tight][rem][mask];
 
    // Return the if result for the
    // current iteration is calculated
    if (res != -1) {
        return res;
    }
    res = 0;
 
    // If reaches the end of the digits
    if (index == dig.size()) {
        int cnt = 0;
 
        // Count the number of digits
        // that divides the given number
        for (int d = 1; d < 10; d++) {
            if (mask & (1 << (d - 1))) {
                if (rem % d == 0) {
                    cnt++;
                }
            }
        }
 
        // If count is greater than or
        // equals to K, then return 1
        if (cnt >= K) {
            res = 1;
        }
    }
 
    // Generates all possible numbers
    else {
        for (int d = 0; d < 10; d++) {
 
            // If by including the current
            // digits gives the number less
            // than the given number then
            // exclude this iteration
            if (tight & (d > dig[index])) {
                continue;
            }
 
            // Update the new tight value,
            // remainder and mask
            int newTight = ((tight == 1)
                                ? (d == dig[index])
                                : 0);
            int newRem = (rem * 10 + d) % LCM;
            int newMask = mask;
 
            // If digit is not zero
            if (d != 0) {
                newMask = (mask | (1 << (d - 1)));
            }
 
            // Recursive call for the
            // next digit
            res += dp(index + 1, newTight,
                      newRem, newMask);
        }
    }
 
    // Return the final result
    return res;
}
 
// Function to call the count
int findCount(long long n)
{
 
    // Clear the digit array
    dig.clear();
    if (n == 0) {
        dig.push_back(n);
    }
 
    // Push all the digit of the number n
    // to digit array
    while (n) {
        dig.push_back(n % 10);
        n /= 10;
    }
 
    // Reverse the digit array
    reverse(dig.begin(), dig.end());
 
    // Intialise the dp array to -1
    memset(memo, -1, sizeof(memo));
 
    // Return the result
    return dp(0, 1, 0, 0);
}
 
int main()
{
 
    long long L = 1, R = 123;
    K = 1;
    cout << findCount(R) - findCount(L - 1);
    return 0;
}

/*#include <iostream>

using namespace std;

long long l, r, sum;

int main (){
    ios_base::sync_with_stdio(0);

    bool add;
    long double div, res;
    long long num;

    cin >> l >> r;
    sum = 0;
    for(long long i = l; i <= r; i++){
        num = i;
        add = true;
        while (num > 1){
            div = num % 10;
            num /= 10;

            if(div == 0){
                add = false;
                break;
            }

            res = i/div;
            if(res != (long long)res){
                add = false;
                break;
            }
        }
        if (add) {
            sum++;
            cout << i << " ";
        }
    }

    cout << "\n" << sum;

    return 0;
}*/