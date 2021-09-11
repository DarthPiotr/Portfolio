#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <iomanip>

#define SIZE 201
#define EDGES 20'000
#define HUGE 0x7FFFFFFF

using namespace std;

int t, n;

// implementacja grafu skierowanego jako macierz sąsiedztwa;
// cap[wierzch_poczat][wierzch_koniec] = pozostały przepływ
int cap[SIZE][SIZE];
// tablica z rodzicami, zapełniana przez BFS, używana przezmaxflow
// -2 - wierzch. począt.; -1 - brak rodzica (nieodwiedzony);
int parent[SIZE];

int bfs(){
    for(int i=1; i<=n; ++i) parent[i] = -1; // wyzeruj rodziców
    queue<int> q;
    int v, flow, nflow;
    parent[1] = -2; // ustaw wierzchołek początkowy,
    q.push(1);      // wstaw go do kolejki
    q.push(HUGE);   // oraz przepływ do niego na nieskończoność

    while(!q.empty()) { // dopóki kolejka jest niepusta
        v = q.front(); q.pop();     // weź z kolejki wierzchołek
        flow = q.front(); q.pop();  // i przepływ do niego
 
        // dla każdej (może też być wstecznej) krawędzi  ...
        for(int to = 1; to <= n; to++){
            // ... prowadzącej do wierzchołka bez rodzica (parent[to] == -1)
            // oraz która ma dostępny przepływ (cap[v][to] > 0)
            if(parent[to] == -1 && cap[v][to] > 0){
                parent[to] = v;     // rodzicem docelowej krawędzi jest ten z którego przyszliśmy
                nflow = min(flow, cap[v][to]);     // oblicz nowy minflow
                if(to == n) return nflow;   // jesli koniec - zakoncz bfs
                q.push(to); // jesli nie - dodaj kolejny do przejrzenia
                q.push(nflow); // oraz przepływ do niego
            }
        }
    }
    // nie ma więcej ścieżek, zwróć flow = 0
    return 0;
}

void showflow(){
    cerr << "\n -   ";
    for(int j = 1; j <= n; ++j) cerr << setw(2) << j << " ";
    cerr << "\n";
    for(int i = 1; i <= n; ++i){
        cerr << setw(2) << i << " | ";
        for(int j = 1; j <= n; ++j){
            cerr << setw(2) << cap[i][j] << " ";
        }
        cerr << "\n";
    }
    cerr << "\n";
}

int maxflow(){
    int ans = 0, nflow, v, p;
    // dopóki można znaleźć ścieżkę
    while((nflow = bfs())){
        // dodaj flow ścieżki do wyniku
        ans += nflow;
        // Updateujemy teraz flow krawędzi w znalezionej ścieżce:
        v = n; // rozpoczynając od końca
        while(v != 1){ // dopóki nie dotrzemy do początkowego wierzchołka
            p = parent[v];  // bierzemy rodzica obecnego wierzchołka
            cap[p][v] -= nflow; // odejmujemy flow z krawędzi w normalnym kierunku
            cap[v][p] += nflow; // ale dodajemy do krawędzi rezydualnej ('wstecznej')
            v = p; // ustawiamy obecny wierzchołek na dotychczasowego rodzica aby kontynuować pętlę
        }
    }
    return ans;
}

int main (){
    ios_base::sync_with_stdio(0);

    int i, j, a;

    cin >> t;
    while (t--){
        cin >> n;
        memset(cap, 0, sizeof(cap));
        for(i = 1; i < n; ++i){
            cin >> j;
            while(j--){
                cin >> a; 
                cap[i][a] = (i == 1 || a == n ? 1 : HUGE);
            }
        }

        //showflow();
        cout << maxflow() << "\n";
    }

    return 0;
}