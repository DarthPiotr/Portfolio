#include <iostream>
#include <bitset>
using namespace std;

#define base 100
#define sizee 10

long long c[sizee];

void dodaj(long long a[], long long b[], int la, int lb)
{
    long long tmp, carry=0, i;
    for (i = 0; i < sizee; i++)
    {
        c[i] = 0;
    }
    for (i = 0; i < max(la, lb); i++)
    {
        tmp = 0;
        if (i < la)
        {
            tmp += a[i];
        }
        if (i < lb)
        {
            tmp += b[i];
        }
        tmp += carry;
        carry = tmp / base;
        c[i] += tmp % base;
    }

    if (carry > 0)
    {
        c[i] += carry;
    }
}

int main()
{
    int a = 1;
    cout << bitset<32>(a << 31) << "\n";


    /*long long a[] = { 1, 6, 6 };
    long long b[] = { 3, 6 };

    dodaj(a, b, 3, 2);

    for (int i = sizee - 1; i >= 0; i--)
    {
        cout << c[i] << ", ";
    }
    cout << "\n";

    return 0;*/
/*
    string a = "0000000000000000000000012345600000234560000";
    bool zera = true;
    for(int i = a.size() - 1; i >= 0; i--){
        cout << i << ": ";
        if(zera){
            // wyjebane
            if(a[i] != '0'){ // aż będzie liczba
                zera = false;
                cout << a[i];
            }
        }
        else {   // potem już zawsze wyświetlaj 
            cout << a[i];
        }
        cout << "\n";
    }
*/
}

/*
index      2   1   0

a[]        6   6   1
wartosc a  6  06  01

b[]            6   3
wartosc b      6  03

60601 + 603 = 61204
             6|12|04

index      2   1   0             
wynik      6  12   4
*/