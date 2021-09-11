#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define SIZE 5
#define BASE 100
#define EXP 2

int va[SIZE] = {0}, vb[SIZE] = {0}, vc[SIZE] = {0};
int main (){

    ios_base::sync_with_stdio(0);

    string a,b;

    cin >> a >> b;

    int base = 1;
    for(int i = 0; i < a.size(); i++){
        if(i % EXP == 0) base = 1;
        //cerr << a[a.size() - i - 1] << "\n";
        va[i / EXP] += (a[a.size() - i - 1]-'0')*base;
        base *= 10;
    }
    for(int i = 0; i < b.size(); i++){
        if(i % EXP == 0) base = 1;
        //cerr << b[b.size() - i - 1] << "\n";
        vb[i / EXP] += (b[b.size() - i - 1]-'0')*base;
        base *= 10;
    }

    int carry = 0;
    int result;
    for(int i = 0; i < SIZE; i++){
        result = carry + va[i] + vb[i];
        if(i+1 < SIZE) vc[i+1] = vc[i] / BASE;
        vc[i] %= BASE;
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