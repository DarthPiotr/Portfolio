#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

#define TAB_SIZE 300'001
#define N_SIZE 7001


using namespace std;
typedef pair<int,int> pii;


int n, e;

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


int findmax(int u, int v){
    if(u == v) return -1;
    cerr << "findmax("<<u<<","<<v<<") called\n";
    bool visited[N_SIZE] = {0};
    int res = -1;
    pii k, l, p, par[N_SIZE];
	queue<pii> q;

	q.push(pii(u, -1));  // start from u
	par[u]=pii(-1,-1); // which has no parent
    visited[u] = true;

	while(!q.empty())
	{
		k = q.front(), q.pop();

		if(k.first == v) break; // finish -> can get to the end

		for(auto i : adj[k.first]) // for each connected node
        {
			if(!visited[i.first]) // if not visited yet
			{
				q.push(i);   // try to visit
				par[i.first] = pii(k.first, i.second);
				visited[i.first] = true;
			}
		}
	}
    if(k.first != v) return -1; // couldnt reach end

    cerr << "PATH\n";
    for(int g = 1; g <= n; ++g){
        cerr << "("<<par[g].first<<","<<par[g].second<<") ";
    }
    cerr << "\n";

    cerr << "path: ";
    k = par[k.first];
    cerr << "START: " << "("<<k.first<<","<<k.second<<")\n";
    while(k.second != -1){
        cerr << k.first;
        p = par[k.first];
        cerr << " == " << p.second << " ==> " << p.first << " // ";
        res = max(res, p.second);
        k = p;
    }
    cerr << k.first << "\n";

    cerr << "max("<<u<<","<<v<<") -> "<<res <<"\n";
    return res;
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
    //memset(parent, 0, sizeof(parent));
    //cerr << "Finding max between " << edges[e].a << " and " << edges[e].b << "\n";
    int max_n = findmax(edges[e].a, edges[e].b);
    //cerr << "Max between " << edges[e].a << " and " << edges[e].b << " is " << max_n << "\n";

    if(edges[e].val == max_n){ // only if same maxw
        treepart[edges[e].id] = true;
        //adj[edges[e].a].push_back(pair<int,int>(edges[e].b, edges[e].val));
        //adj[edges[e].b].push_back(pair<int,int>(edges[e].a, edges[e].val));
    }
}

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