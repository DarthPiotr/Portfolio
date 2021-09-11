#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int t;
ll n, m, mst;

ll ceil_div(ll a, ll b){
    return a/b + ((a%b) != 0);
}

int main (){
    ios_base::sync_with_stdio(0);
    cin >> t;
    while(t--){
        cin >> n >> m >> mst;

        if(m == n-1){ // w tym n == 2
            cout << mst << "\n";
            continue;
        }

        ll pelny = ((n-1)*(n-2))/2; // liczba krawedzi w grafie pelnym, o jeden mniejszym niz nasz

         // najpierw probujemy zrobic graf jak najbardziej pelny
         // ale z jedna odstajaca krawedzia
        if(m <= pelny){
            // wtedy mst powiekszamy o:
            // (liczba krawedzi ktore mamy - liczba krawedzi w mst) = pozostale krawedzie maja wagi 1
            cout << mst + m - (n - 1) << "\n";
            continue;
        }


        
        ll krawedzie_do_odstajacego = m - pelny; // ile krawedzi laczy sie z tym odstajacym
        ll wagi_krawedzi_do_odstajacego = mst - (n-2);  // suma krawedzi laczacych sie z tym odstajacym
                                                        // to mst pomniejszone o dlugosc mst mniejszego o 1 grafu
        // wynikiem na ten moment jest caly podgraf pelny o wagach 1
        // plus rowno rozlozone wagi mst po krawedziach do odstajacego
        ll wynik = pelny + wagi_krawedzi_do_odstajacego * krawedzie_do_odstajacego;
        
        // jesli odstajacych krawedzi jest za duzo wzgledem podgrafu
        if(krawedzie_do_odstajacego*(n-2) > pelny){
            ll zapelnione = (wagi_krawedzi_do_odstajacego - 1)/(n-1);
            wynik += (pelny - krawedzie_do_odstajacego*(n-2)) * zapelnione;
            ll nowe_wagi = wagi_krawedzi_do_odstajacego - (n-2)*zapelnione;
            if(nowe_wagi - 1 >= zapelnione+2){
                ll usun = (nowe_wagi-1) - (zapelnione+2) + 1;
                ll zmiana = usun*(n-1) - usun*(usun+1) / 2 - krawedzie_do_odstajacego*usun;
                if(zmiana < 0)
                    wynik += zmiana;
            }
        }
        

        cout << wynik << "\n";
    }
    return 0;
}
// to zadanie bylo szalenie trudne i nie jestem do konca przekonany dlaczego dziala
// posilkowalem sie rozwiazaniami z hackerranka i chyba udalo mi sie pojac mniej wiecej
// jak ma dzialac