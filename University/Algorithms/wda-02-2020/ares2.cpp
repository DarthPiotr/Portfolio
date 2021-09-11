#define R(p) rand()%('9'-(p)+1)+(p) 
#define P(p) putc((p),stdout)
#define PP(p) P(R(p)) 

#include <iostream>
#include <cstdlib>

#include <cstdio>

using namespace std;


void gen(int x) 
{
    if (x) PP('1'); else PP('0');
    for(;x;x--) PP('0');
}

int main()
{
    int a, d, n;
    cin >> a; srand(a); 
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