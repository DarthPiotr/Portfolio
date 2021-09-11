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
int cap[SIZE][SIZE];
vector<int> graph[SIZE];

int parent[SIZE];
int bfs(){
    bool visited[SIZE] = {0};
    for(int i=1; i<=n; ++i) parent[i] = -1;
    queue<int> q;
    int v, flow, nflow;
    parent[1] = -2;
    q.push(1);
    q.push(HUGE);

    while(!q.empty()) {
        v = q.front(); q.pop();
        flow = q.front(); q.pop();
        visited[v] = true;

        //for(int to : graph[v]){ // dla kazdej krawedzi 
        for(int to = 1; to <= n; to++) { // dla jeszcze bardziej każdej krawędzi
            if(parent[to] == -1 && cap[v][to] > 0){ // jesli jeszcze nie wystepuje i ma wolny przeplyw
                parent[to] = v;                    // zaznacz skad przyszlismy
                nflow = min(flow, cap[v][to]);     // oblicz nowy minflow
                if(to == n) return nflow;          // jesli koniec - zakoncz bfs
                q.push(to);                        // jesli nie - dodaj kolejny do przejrzenia
                q.push(nflow);
            }
        }
    }
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

int solve(){
    int ans = 0, nflow, v, p;


    while((nflow = bfs())){
        ans += nflow;
        v = n;
        cerr << "path: ";
        while(v != 1){
            cerr << v << " <- ";
            p = parent[v];
            cap[p][v] -= nflow;
            cap[v][p] += nflow;

            v = p;
        }
        cerr << "1\n";
        showflow();

    }

    return ans;
}

/*int solve()
{    
    int flow=0;
    while(1)
    {
        queue<int>Q;
        memset(parent,-1,sizeof (parent));
        Q.push(1);
        int path=HUGE;
        parent[1]=1;
        while(!Q.empty())
        {
            int u=Q.front();Q.pop();
            for(int i=1;i<=n;i++)
            {
                if(parent[i]==-1 && cap[u][i]>0)
                {
                    path=min(path,cap[u][i]);
                    parent[i]=u;
                    if(i!=n)
                    Q.push(i);
                    else
                    {
                        while(parent[i]!=i)
                        {
                            u=parent[i];
                            cap[u][i]-=path;
                            cap[i][u]+=path;
                            i=u;
                        }
                        flow+=path;
                        break;
                    }
                }
            }
        }
        if(parent[n]==-1)
        break;
    }
    return flow;
}*/

int main (){
    ios_base::sync_with_stdio(0);

    int i, j, a;

    cin >> t;
    while (t--){
        cin >> n;
        memset(graph, 0, sizeof(graph));
        memset(cap, 0, sizeof(cap));
        for(i = 1; i < n; ++i){
            cin >> j;
            while(j--){
                cin >> a; 
                graph[i].push_back(a);
                cap[i][a] = (i == 1 || a == n ? 1 : HUGE);
            }
        }

        //showflow();
        cout << solve() << "\n";
    }

    return 0;
}