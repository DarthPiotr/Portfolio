#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n, c, t, k;
int stalls[100000];

int binSearch(int beg, int end){
    
    if(beg == end)
        return beg;

    int pre, curr, i, cnt = 1;
    int mid = (end+beg)/2 + 1;

    // zaczynamy od elementow 0 i 1
    pre = stalls[0];
    for(i = 1; i < n; i++){
        curr = stalls[i];
        // jesli odleglosc jest przynajmniej taka jak zakladamy
        if(curr - pre >= mid){
            // dodaj krowe i zapamietaj obecna pozycje
            cnt++;
            pre = curr;
        }
        // jesli mozna tak rozmiescic, szukaj po prawej
        if(cnt >= c){
            return binSearch(mid,end);
        }
    }
    // jesli nie mozna, szukaj po lewej
    return binSearch(beg, mid-1);
}

int main(){

    ios_base::sync_with_stdio(false);

    cin >> t;

    for(int z = 0; z < t; z++){
        cin >> n >> c;

        for(k = 0; k < n; k++){
            cin >> stalls[k];
        } 
        // zeby algorytm dzialal, potrzebuje rosnacej listy miejsc       
        sort(stalls, stalls+n);

        // (stalls[n-1]-stalls[0])/(c-1) 
        // ogranicza maksymalna odleglosc do rzeczywistego maksimum
        // w najbardziej optymistycznym wariancie
        cout << binSearch(1, (stalls[n-1]-stalls[0])/(c-1)) << "\n";
    }
    return 0;
}