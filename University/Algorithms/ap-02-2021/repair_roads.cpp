#include <iostream>
#include <vector>
#include <cstring>

#define _DEBUG_

using namespace std;

int t, n;

struct vert{
    int index;
    vector<vert*> conn;
} graph[10000];
vector<int> connections[10000];

int DFS_num[10000];
int cv;
void DFS_bridges(int v, int p){
    
}

int main (){
    ios_base::sync_with_stdio(0);
    int i, j, a, b;

    cin >> t;
    while(t--){
#ifdef _DEBUG_
        cerr << "\t=== NEW CASE ===\n";
#endif
        cin >> n;
        memset(graph, 0, sizeof(graph));
        memset(connections, 0, sizeof(connections));

        for(i = 0; i < n-1; ++i){
            cin >> a >> b;

            graph[i].index = i;
            for(auto & e : connections[a]) {
                graph[i].conn.push_back(&graph[e]);
                graph[e].conn.push_back(&graph[i]);
            }
            for(auto & e : connections[b]) {
                graph[i].conn.push_back(&graph[e]);
                graph[e].conn.push_back(&graph[i]);
            }
            
            connections[a].push_back(i);
            connections[b].push_back(i);
        }

#ifdef _DEBUG_
        for(i = 0; i < n-1; ++i){
            cerr << i << ": ";
            for(auto &e: graph[i].conn) cerr << e->index << " ";
            cerr << "\n";
        }
#endif
        memset(DFS_num, 0, sizeof(DFS_num));
        cv = 0;
        DFS_bridges(0, -1);

    }

    return 0;
}