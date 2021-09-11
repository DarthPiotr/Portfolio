#include <iostream>
#include <vector>
#include <algorithm>

#define TAB_SIZE 300'001
#define N_SIZE 7001

using namespace std;

struct edge{
    int id;
    int a, b, val;
    edge() {}
    edge(int a, int b, int v) : a(a), b(b), val(v) {}
}edges[TAB_SIZE];
bool treepart[TAB_SIZE] = {0};

bool compare(const edge& a, const edge& b){
    if(a.val == b.val)
        return a.val + a.a + a.b < b.val + b.a + b.b;
    return a.val < b.val;
}

int parent[N_SIZE] = {0};
int csize[N_SIZE] = {0};

int find(int a){
    if(a == parent[a]) return a;

    return parent[a] = find(parent[a]);
}

int unite(int e, int maxw){
    int a = find(edges[e].a), b = find(edges[e].b);
    
    if(a != b){ // different groups - unite
        if(csize[a] < csize[b]) swap(a, b);

        csize[a] += csize[b];
        parent[b] = parent[a];
        
        treepart[edges[e].id] = true;
        maxw = edges[e].val;
        return maxw;
    }
    if(edges[e].val == maxw) // only if same maxw
        treepart[edges[e].id] = true;
    
    return maxw;
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

    int a, b, i, j;

    cin >> n >> e;

    for(i = 1; i <= n; ++i){
        parent[i] = i;
        csize[i] = 1;
    }

    for(j = 0; j < e; ++j){
        cin >> a >> b >> i;
        edges[j].id = j;
        edges[j].a = a;
        edges[j].b = b;
        edges[j].val = i;
    }

    sort(edges, edges+e, compare);

    //debug();

    int maxw = 0;
    for(i = 0; i < e; ++i){
        maxw = unite(i, maxw);
    }
    for(i = 0; i < e; ++i){
        cout << (treepart[i] ? "TAK" : "NIE") << "\n";
    }

    return 0;
}