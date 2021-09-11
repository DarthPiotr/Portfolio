#define R(p) rand()%('9'-(p)+1)+(p) // makropolecenie
#define P(p) putc((p),stdout)
#define PP(p) P(R(p)) // makropolecenia zagnie��d��one

#include <iostream>
#include <cstdlib>

#include <cstdio>

using namespace std;

/* funkcja generuj��ca ci��g cyfr */
void gen(int x) 
{
    if (x) PP('1'); else PP('0');
    for(;x;x--) PP('0');
}
//  jednoliniowy komentarz \
    dwuliniowy
int main()
{
    int a, d, n;
    cin >> a; srand(a); /* inicjalizacja generatora
        liczb pseudolosowych /* */
    cin >> d; cin >> n; cout << n << endl;
    for(;n;n--)
    {
        gen(rand()%d);  P(' ');
        gen(rand()%d);  P('\n');
        cout << "    \"   \'   "[0];
        cout << " //   \"   \'   "[1];
        cout << "    \" //  \'   "[2];
        cout << "    \"   \'  // "[3];



        cout << '\'' << '\\' << '\"';

        cout << "// lol \n";
        cout << "/*    XDDDD";
        cout << "fdsbibyd */";
    
    }
    return 0;
}