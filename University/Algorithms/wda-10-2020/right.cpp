#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

#define PI ((long double)3.141592653589793238)

using namespace std;

struct pt{
    int x,y;
    pt() : x(0), y(0) {}
} tab[1500];

int main (){

    ios_base::sync_with_stdio(0);

    short n, anglen;
    int i,j;
    long double alpha, angles[1500];
    long double weirderror = 1e-9; //atan2(1,0)-PI/2 //1.7949e-09;
    //cerr << weirderror << "\n\n";
    long long res = 0;
    cin >> n;
    for(i = 0; i < n; i++)
        cin >> tab[i].x >> tab[i].y;

    for(i = 0; i < n; i++){
        anglen=0;
        for(j = 0; j < n; j++){
            if(i != j){
                // atan2(delta y, delta x) - liczy kat nachylenia wektora
                // liczymy kat nachylenia prostej wzgledem punktu tab[i]
                alpha = atan2(tab[j].y-tab[i].y, tab[j].x-tab[i].x);
                // odbijamy spod osi X
                if(alpha<0) alpha+=PI;
                angles[anglen++] = alpha;
            }
        }
        // sortujemy dla latwiejszego wyszukiwania potem
        sort(angles, angles+anglen);

        // jako ze odbilismy do gory, to mozemy tylko liczyc z przedzialu od 0 do pi
        // a ze dodajemy kat prosty czyli pi/2, to starczy liczyc od 0 do pi/2
        for(j = 0; j < anglen && angles[j] < PI/2+weirderror; j++){
            //cerr << setw(10) << angles[j] << "\n";
            /*cerr << angles[j]*180/PI << ", r ("<< (angles[j]*180/PI+90) <<"): "<<
                upper_bound(angles, angles+anglen,angles[j]+PI/2) - lower_bound(angles, angles+anglen,angles[j]+PI/2)
               // + upper_bound(angles, angles+anglen,angles[j]-PI/2) - lower_bound(angles, angles+anglen,angles[j]-PI/2)
                <<"\n";*/
            // upper bound - zwraca jakby indeks ostatniego wystapienia
            // lower bound - zwraca jakby indeks pierwszego wystapienia
            // dodajemy tyle ile bylo linii z katem o 90 stopni wiekszym
            res += upper_bound(angles, angles+anglen,angles[j]+PI/2+weirderror) - lower_bound(angles, angles+anglen,angles[j]+PI/2-weirderror)
                //+ upper_bound(angles, angles+anglen,angles[j]-PI/2) - lower_bound(angles, angles+anglen,angles[j]-PI/2)
                ;
        }
        //cerr << "---\n";
    }

    cout << res << "\n";

    return 0;
}