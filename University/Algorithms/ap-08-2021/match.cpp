// !!! Jest to zmodyfikowany kod testowy w ramach
// przygotowania do egzaminu. 
// Uprzejmie proszę do oceny proszę brać pod uwagę pierwszy kod który przeszedł testy.

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

#define SIZE 100'002

using namespace std;

int n, m, total;


// <1..n>       - część A // szczegół
// <n+1..total> - część B //   implementacyjny
// graph - lista sąsiedztwa
vector<int> graph[SIZE];
bool visited[SIZE]; // odwiedzone wierzchołki
int match[SIZE];    // dopasowania

// znajduje dopasowanie do wierzchołka v
// oraz zwraca czy przebiegło to pomyślnie
bool findmatch(int v){
    // dla każdego u - sąsiada v
    for(auto u : graph[v]) {
        // jeśli sąsiad jest nieodwiedzony
        if(!visited[u]){
            // oznacz go jako odwiedzony
            visited[u] = true;
            // jeśli u nie ma dopasowania
            // albo udało się znaleźć inne dopasowanie
            // do obecnego skojarzenia u (wydłużenie ścieżki)
            if(match[u] == -1 || findmatch(match[u])){
                // to zaznacz że u i v są dopasowane
                match[u] = v;
                match[v] = u;
                // dopasowanie zakończone sukcesem
                return true;
            }
        }
    }
    // nie można dopasować do żadengo sąsiada
    return false;
}

// zwraca maksymalną liczbę dopasowań
int maxmatch(){
    int matches = 0;
    // dla każdego wierzchołka w części A
    for(int i = 1; i <= n; ++i){
        // zresetuj odwiedzone
        memset(visited, 0, sizeof(visited));
        // próbuj znaleźć dopasowanie do i
        // jeśli się udało to zwiększ licznik
        if(findmatch(i)) ++matches;
    }
    // zwróć liczbę dopasowań
    return matches;
}

int main (){
    ios_base::sync_with_stdio(0);

    int a, b, p;    

    cin >> n >> m >> p;
    total = n+m;
    for(a = 0; a <= total; ++a) match[a] = -1;
    while(p--) {
        cin >> a >> b;
        graph[a].push_back(b+n);
        graph[b+n].push_back(a);
    }

    cout << maxmatch() << "\n";

    for(int i = 0; i <= n; ++i)
        cerr << i << " -> " << match[i] << "\n";

    return 0;
}