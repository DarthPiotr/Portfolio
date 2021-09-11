#include <iostream>

#define SIZE 8 // potega dwojki

using namespace std;

struct tree{
    int tab[2*SIZE];

    // query_l - początek przedziału zapytania
    // query_r - koniec przedziału zapytania
    // node - node do przepytania (zaczynamy od korzenia)
    // node_l - początek przedziału node'a (szczegół implementacyjny)
    // node_r - koniec przedziału node'a (szczegół implementacyjny)
    int query(int query_l, int query_r, int node, int node_l, int node_r){
        // jeśli zapytanie nie ma części wspólnej z przedziałem node'a zwróć zero
        // (obejmuje też przypadki kiedy zeszliśmy do liścia)
        if(query_l > node_r || query_r < node_l) return 0; 
                 
        // jeśli node zawiera się całkowicie w zapytaniu, zwróć jego wartość (nie schodzimy głębiej)
        // (obejmuje też przypadki kiedy zeszliśmy do liścia)
        if(query_l <= node_l && query_r >= node_r) return tab[node];

        // pozostałe przypadki - node częściowo pokrywa się z przedziałem
        // zwróć sumę odpytań jego dzieci
        int mid = (node_l+node_r)/2; // wyliczenie końca przedziału lewego dziecka żeby przekazać do funkcji, szczegół implementacyjny
        return  query(query_l, query_r, 2*node, node_l, mid) + 
                query(query_l, query_r, 2*node+1, mid+1, node_r);
    }

    // node - node do aktualizacji (zaczynamy od liścia)
    // value - wartość do wpisania
    void update(int node, int value){
        // jeśli jesteśmy w liściu
        if(node >= SIZE) {
            // wpisujemy nową wartość do liścia
            tab[node] = value;
            // po czym aktualizujemy rodzica
            update(node/2, value);
        }
        // jeśli nie jesteśmy w liściu
        else{
            // aktualizujemy wartość node'a: jest to suma jego dzieci
            tab[node] = tab[2*node] + tab[2*node+1];
            // jeśli jesteśmy w korzeniu to kończymy
            if(node == 1) return;
            // w przeciwnym wypadku aktualizujemy rodzica
            update(node/2, value);
        }
    }

    void updateRange(int query_l, int query_r, int value){
        for(int i = query_l; i <= query_r; ++i)
            update(SIZE + i, value);
    }
};

int main (){

    ios_base::sync_with_stdio(0);

    tree t;
    t.updateRange(0,6,2);


    cout << t.query(1,7,1,0,7) << "\n";

    return 0;
}