// Zlozonosc O(n^2)

#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

#define SIZE 10000
#define BASE 100000000
#define EXP 8

int va[SIZE] = {0}, vb[SIZE] = {0}, vc[SIZE] = {0}, vres[SIZE] = {0};
int main(){

    ios_base::sync_with_stdio(0);

    string a,b;

    cin >> a >> b;

    int base = 1;
    for(int i = 0; i < (int)a.size(); i++){
        if(i % EXP == 0) base = 1;
        //cerr << a[a.size() - i - 1] << "\n";
        va[i / EXP] += (a[a.size() - i - 1]-'0')*base;
        base *= 10;
    }
    for(int i = 0; i < (int)b.size(); i++){
        if(i % EXP == 0) base = 1;
        //cerr << b[b.size() - i - 1] << "\n";
        vb[i / EXP] += (b[b.size() - i - 1]-'0')*base;
        base *= 10;
    }

    long long carry;
    for(int i = 0; i < SIZE; i++){   // vb
        memset(vres, 0, sizeof(int)*SIZE);
        for(int j = 0; j < SIZE; j++){  // va
            vres[i+j] = va[j]*vb[i];
            vres[i+j+1] = vres[i+j]/BASE;
            vres[i+j] %= BASE;
        }

        carry = 0;
        for(int i = 0; i < SIZE; i++){
            vc[i] = carry + vres[i] + vc[i];
            carry = vc[i] / BASE;
            vc[i] %= BASE;
        }

    }



    bool flag = true;
    for(int i = SIZE-1; i >= 0; i--){
        if(flag){
            if(vc[i] != 0){
                flag = 0;
                cout << vc[i];
            }
        }
        else{
            cout << setfill('0') << setw(EXP) << vc[i];
        }
    }

    return 0;
}