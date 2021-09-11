#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

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
vector<pair<int,int>> adj[N_SIZE];

bool compare(const edge& a, const edge& b){
    return a.val < b.val;
}

int parent[N_SIZE] = {0};
int csize[N_SIZE] = {0};

int find(int a){
    if(a == parent[a]) return a;

    return parent[a] = find(parent[a]);
}

bool visited[N_SIZE];
int findmax(int u, int v){
    //cerr << "findmax("<<u<<","<<v<<") called\n";
    if(u == v) return -1;
    
    int n_mx = -1;
    for(auto e : adj[u]){
        if(!visited[e.first]){
            visited[e.first] = true;
            if(e.first == v) {
                //cerr << "Max ("<<u<<","<<v<<") is " << e.second << " (neighbour)\n";
                return e.second;
            }
            n_mx = max(max(n_mx, e.second), findmax(e.first, v));
        }
    }
    //cerr << "Max ("<<u<<","<<v<<") is " << n_mx << "\n";
    return n_mx;
}

void unite(int e){
    int a = find(edges[e].a), b = find(edges[e].b);
    
    if(a != b){ // different groups - unite
        if(csize[a] < csize[b]) swap(a, b);

        csize[a] += csize[b];
        parent[b] = parent[a];

        adj[edges[e].a].push_back(pair<int,int>(edges[e].b, edges[e].val));
        adj[edges[e].b].push_back(pair<int,int>(edges[e].a, edges[e].val));
        //cerr << "Added edge " << edges[e].a << " <-> " << edges[e].b << "("<<edges[e].val<<")" << "\n";
        
        treepart[edges[e].id] = true;
        return;
    }
    // make sure can add
    memset(visited, 0, sizeof(visited));
    //cerr << "Finding max between " << edges[e].a << " and " << edges[e].b << "\n";
    int max_n = findmax(edges[e].a, edges[e].b);
    //cerr << "Max between " << edges[e].a << " and " << edges[e].b << " is " << max_n << "\n";

    if(edges[e].val == max_n){ // only if same maxw
        treepart[edges[e].id] = true;
        adj[edges[e].a].push_back(pair<int,int>(edges[e].b, edges[e].val));
        adj[edges[e].b].push_back(pair<int,int>(edges[e].a, edges[e].val));
    }
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
        //adj[a].push_back(pair<int,int>(b, i));
        //adj[b].push_back(pair<int,int>(a, i));
        edges[j].val = i;
    }

    sort(edges, edges+e, compare);

    //debug();

    for(i = 0; i < e; ++i){
        unite(i);
    }
    for(i = 0; i < e; ++i){
        cout << (treepart[i] ? "TAK" : "NIE") << "\n";
    }

    return 0;
}