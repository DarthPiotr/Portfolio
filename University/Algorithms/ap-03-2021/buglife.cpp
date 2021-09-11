#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct vert{
    int index;
    int color;
    vector<vert*> edges;
} graph[2001];

int n, t, v, e;

int main (){

    ios_base::sync_with_stdio(0);

    int i, j, a, b;
    bool error;

    cin >> t;
    for(n = 1; n <= t; ++n){
        cin >> v >> e;

        //cerr << "===CASE===\n";

        memset(graph, 0, sizeof(graph));
        for(i = 0; i < e; ++i){
            cin >> a >> b;
            graph[a].index = a;
            graph[a].edges.push_back(&graph[b]);
            graph[b].index = b;
            graph[b].edges.push_back(&graph[a]);
        }

        error = false;
        for(i = 1; i <= v; ++i){
            queue<vert*> q;

            if(graph[i].color != 0) continue;

            graph[i].color = 1;

            //cerr << "vert: " << graph[i].index << " ("<<graph[i].color<<")\n";

            for(j = 0; j < (int)graph[i].edges.size(); ++j){
                if(graph[i].edges[j]->color == 0){
                    graph[i].edges[j]->color = 2;
                    q.push(graph[i].edges[j]);
                }
                else if(graph[i].edges[j]->color == graph[i].color){
                    error = true;
                    break;
                }
            }
            if(error) break;

            while(!q.empty()){
                vert* ver = q.front(); q.pop();
                cerr << "vert: " << ver->index << " ("<<ver->color<<")\n";
                for(j = 0; j < (int)ver->edges.size(); ++j){
                    if(ver->edges[j]->color == 0){
                        ver->edges[j]->color = ver->color == 1 ? 2 : 1;
                        q.push(ver->edges[j]);
                    }
                    else if(ver->edges[j]->color == ver->color){
                        error = true;
                        break;
                    }
                }
            }
            if(error) break;
        }

        cout << "Scenario #"<<n<<":\n";
        if(error)
            cout << "Suspicious bugs found!\n";
        else
            cout << "No suspicious bugs found!\n";
    }

    return 0;
}