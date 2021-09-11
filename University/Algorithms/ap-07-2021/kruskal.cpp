#include <iostream>
#include <vector>
#include <algorithm>

#define TAB_SIZE 5001

using namespace std;

struct edge{
    int a, b, val;
    edge() {}
    edge(int a, int b, int v) : a(a), b(b), val(v) {}
}edges[TAB_SIZE];
int ecnt = 0;

bool compare(const edge& a, const edge& b){
    if(a.val == b.val)
        return a.val + a.a + a.b < b.val + b.a + b.b;
    return a.val < b.val;
}
/*struct graph{
    int index;
    vector<edge> edges;
} graph[TAB_SIZE];*/

// tablica z rodzicami danego wierzchołka
// na początku parent[i] = i
int parent[TAB_SIZE] = {0};
// tablica z rozmiarami drzewa (liczba wierzchołków)
// w którym znajduje się dany wierzchołek
// początkowo wszędzie 1
int csize[TAB_SIZE] = {0};

// znajduje korzeń drewa w którym znajduje się a
// a - wierzchołek grafu
int Find(int a){
    // jeśli a jest swoim rodzicem to znaczy że
    // jest korzeniem
    if(a == parent[a]) return a;

    // w przeciwnym wypadku, znajdź korzeń rodzica a
    // i przypisz go jako bezpośredniego rodzica a
    // po czym zwróć ten korzeń
    return parent[a] = Find(parent[a]);
}

// scala drzewa do których należą a i b
bool Union(int a, int b){
    // znajdź korzenie drzew do których należą a i b
    int pa = Find(a), pb = Find(b);
    // jeśli należą do różnych drzew
    if(pa != pb){
        // upewnij się że a należy do większego drzewa
        // (optymalizacja, szczegół implementacyjny)
        if(csize[pa] < csize[pb]) swap(pa, pb);

        // dołącz drzewo b do drzewa a:
        csize[pa] += csize[pb]; // dołącz liczbę wierzchołków
        parent[pb] = parent[pa]; // przypisuje nowy korzeń
        return true;
    }
    return false;
}

int n, e;

/*void debug(){
    cerr << "EDGES:\n";
    for(int i = 0; i < ecnt; ++i){
        cerr << edges[i].a << "<->" << edges[i].b << " ("<<edges[i].val<<")\n";
    }
}*/

int main (){

    ios_base::sync_with_stdio(0);

    int a, b, i;

    cin >> n >> e;

    for(i = 1; i <= n; ++i){
        parent[i] = i;
        csize[i] = 1;
    }

    while(e--){
        cin >> a >> b >> i;
        edges[ecnt].a = a;
        edges[ecnt].b = b;
        edges[ecnt].val = i;
        ecnt++;
    }

    sort(edges, edges+ecnt, compare);

    //debug();

    long long res = 0;
    for(i = 0; i < ecnt; ++i){
        if(Union(edges[i].a, edges[i].b))
            res += edges[i].val;
    }
    cout << res << "\n";

    return 0;
}