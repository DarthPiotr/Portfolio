#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct vert;
struct edge{
    int len;
    vert* to;
};

struct vert{
    int index;
    vector<edge> conn;
} graph[50001];

int t, n;

int dijkstra(int beg, int &max_index){
    int tab[50001], v, maxlen=0;
    memset(tab, 0x77, sizeof(tab));

    queue<int> q;
    q.push(beg);
    q.push(0);
    tab[beg] = 0x77777776;

    while(!q.empty()){
        v = q.front(); q.pop();
        tab[v] = q.front(); q.pop();
        cerr << "To #" << v << " len: " << tab[v] << "\n";

        if(tab[v] > maxlen){
            max_index = v;
            maxlen = tab[v];
        }
        //cerr << "Getting chldren of "<<v<<"... ("<<graph[v].conn.size()<<")\n";
        for(edge &c : graph[v].conn){
            //cerr << "Checking " << c.to->index << "\n";
            if(tab[c.to->index] == 0x77777777) {
                q.push(c.to->index);
                q.push(tab[v] + c.len);
                tab[c.to->index] = 0x77777776;
            }
        }
    }

    return maxlen;
}

int main (){
    ios_base::sync_with_stdio(0);
    int a, b, l, i, mx;
    edge e;

    cin >> t;

    while(t--){
        cin >> n;
        memset(graph, 0, sizeof(graph));
        for(i = 0; i < n-1; ++i){
            cin >> a >> b >> l;
            e.len = l;

            e.to = &graph[b];
            graph[a].index = a;
            graph[a].conn.push_back(e);

            e.to = &graph[a];
            graph[b].index = b;
            graph[b].conn.push_back(e);       
        }
        /*cerr << "\t=== NEW CASE ===\n";
        cerr << "Graph:\n";
        for(i = 1; i <= n; ++i){
            cerr << i << ": ";
            for(auto c : graph[i].conn) cerr << c.to->index << " ";
            cerr << "\n";
        }*/

        
        dijkstra(1, mx);
        cout << dijkstra(mx, i) << "\n";
    }

    return 0;
}