#include <iostream>
#include <cmath>

using namespace std;

/*
    x(a*a - c*c) = y(d*d - b*b)

    x (a*a - c*c)
    -------------  = (d*d - b*b)
          y
*/

int tab[1000001];

int main (){
    //ios_base::sync_with_stdio(0);

    int n, x, y, a, b;
    double res, ptr;
    int cnt = 0;
    cin >> n >> x >> y;

    for(a = 0; a <= n; ++a) // znajdz wszystkie roznice kwadratow
        for(b = a; b <= n; ++b)
            tab[b*b - a*a]++;

    for(a = 0; a <= n*n; ++a){
        if(tab[a] > 0){
            //cout << "Trying with a: " << a << " (x " << tab[a] << "); ";
            res = (a * x) / (double) y;
            //cout << "res: " << res << " (x " << tab[(int)res] << "); ";
            if(modf(res, &ptr) == 0.0 && res <= n*n){
                cout << a << ":" << res << "->" << tab[a] * tab[(int)res] << " ";
                if(a == 0)
                    cnt += tab[a] * tab[(int)res];
                else
                    cnt += tab[a] * tab[(int)res] * 2;
            }
            //cout << "\n";
        }
    }
    cout << "\n" << cnt << "\n";

    return 0;
}