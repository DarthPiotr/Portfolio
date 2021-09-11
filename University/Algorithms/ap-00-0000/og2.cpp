#include <iostream>
using namespace std;
int tab[1000][1000];
int wyniki[1000000];
int main ()
{
int n, x, y, i, j, p, i_iloczyn, rez;
double d_iloczyn;

//while(
    cin >> n >> x >> y;//)
//{

    if((n * 2 < x || n * 2 < y) && x != y)
    {
        rez = (n + 1) * (n + 1);
    }

    else
    {
        rez = 0;
        double ulamek = double(x) / double(y);
        //cout << ulamek << "\n";

        for(i = 0; i < n * n; i++)
        {
            wyniki[i] = 0;
        }

        p = 1;
        for(i = 0; i < n; i++)
        {
            for(j = p; j <= n; j++)
            {
                wyniki[(j * j) - (i * i)]++;
            }
            p++;
        }

        for(i = 0; i <= n * n; i++)
        {
            //cout << i << ": " << wyniki[i] << "\n";
        }

        for(i = 1; i <= n * n; i++) //do kwadratu z n starczy
        {
            if(wyniki[i] != 0)
            {
                d_iloczyn = ulamek * i;
                i_iloczyn = ulamek * i; //chce tylko liczby calkowite
                if(i_iloczyn == d_iloczyn)
                {
                    rez += wyniki[i_iloczyn] * wyniki[i];
                    cout << i << ":" << i_iloczyn << "->" << wyniki[i] * wyniki[i_iloczyn] << " ";
                    //cout << wyniki[i_iloczyn] << " ";
                    //cout << i << ":" << i_iloczyn << " rez - " << rez << " ";
                }
            }
        }
        //cout << "\n" << rez << "\n";
        rez = (rez * 2) + (n + 1) * (n + 1);
    }

    cout << "\n" << rez << "\n";
//}

return 0;
}