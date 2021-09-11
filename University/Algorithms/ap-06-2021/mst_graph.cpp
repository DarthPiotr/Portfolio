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
            // (liczba krawedzi ktore mamy - liczba krawedzi w mst) => pozostale krawedzie maja wagi 1
            cout << mst + m - (n - 1) << "\n";
            continue;
        }


        
        ll krawedzie_do_odstajacego = m - pelny; // ile krawedzi laczy sie z tym odstajacym
        ll wagi_krawedzi_do_odstajacego = mst - (n-2);  // suma krawedzi laczacych sie z tym odstajacym
                                                        // to mst pomniejszone o dlugosc mst mniejszego o 1 grafu
        
        // wynikiem na ten moment jest caly podgraf pelny o wagach 1
        // plus rowno rozlozone wagi mst po krawedziach do odstajacego
        ll wynik = pelny + wagi_krawedzi_do_odstajacego * krawedzie_do_odstajacego;

        // jesli odstajacych krawedzi jest wiecej niz polowa krawedzi drzewa calego grafu
        if(n-1 < krawedzie_do_odstajacego*2){
            // to da sie wprowadzic pewne optymalizacje.
            // proba zrownowazenia grafu aby otrzymac mniejsze wartosci ogolnie
            
            // obliczenie o ile mozna zwiekszyc wagi krawedzi w podgrafie pelnym
            // od wyniku odejmujemy o ile sie zmienila wartosc wszystkich krawedzi
            // wynik = p + wdo*kdo - [zm(kdo(n-2)-p)]
            //       = p + wdo*kdo - zm*kdo(n-2) + zm*p
            //       = p(1+zm) + kdo(wdo - zm(n-2))
            //                       ^^^^^^^^^^^^^
            //                nowa waga prowadzacych do odstajacego
            ll zmiana_reszty = (wagi_krawedzi_do_odstajacego - 1)/(n-1); // prawie cala wage probujemy jakby rozlozyc na wszystkie krawedzie w mst
            wynik -= (krawedzie_do_odstajacego*(n-2) - pelny) * zmiana_reszty;
            ll nowe_wagi = wagi_krawedzi_do_odstajacego - (n-2)*zmiana_reszty;

            // gdyby chciec te zmiane rozlozyc na cale drzewo i wartosci krawedzi
            // do odstajacego wyszlyby przynajmniej 3, to istnieje szansa lepszego rozkladu
            // wtedy staramy sie rozlozyc rownomiernie, uzywajac tylko dwoch najmniejszych wag
            // ktore wynikalyby z rozkladu mst troche jakby dirichletem
            if(wagi_krawedzi_do_odstajacego - zmiana_reszty*(n-1) >= 3){
                ll usun = wagi_krawedzi_do_odstajacego - zmiana_reszty*(n-1) - 3 + 1; // ile krawedzi bedzie mialo mniejsze wagi
                ll zmiana = usun*(n-1) - usun*(usun+1) / 2 - krawedzie_do_odstajacego*usun; // o ile realnie zmieni sie waga w tym przypadku
                if(zmiana < 0) // uwzglednij, jesli sie oplaca, tj wyszlo na minusie
                    wynik += zmiana;
            }
        }        

        cout << wynik << "\n";
    }
    return 0;
}
// dlugie godziny zostaly spedzone nad analiza tego kodu zeby zrozumiec jak on naprawde dziala