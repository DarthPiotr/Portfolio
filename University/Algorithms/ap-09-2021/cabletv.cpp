#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <cstring>

#define SIZE 51
#define HUGE 0x7FFFFFFF

using namespace std;

int test, n, m;

int cap_orig[SIZE][SIZE];
int cap[SIZE][SIZE];
vector<int> graph[SIZE];


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

int path[SIZE];
bool bfs(int beg, int end) { // check if any paths are possible
    bool visited[SIZE] = {0};
    int v;
    memset(path, 0, sizeof(path));
    queue<int> q;

    q.push(beg);  // start from 1
    path[beg]=-1; // which has no parent

    while(!q.empty())
    {
        v = q.front(), q.pop();

        if(v == end) return true; // finish -> can get to the end

        //for(int i : graph[v]) // for each connected node
        for(int i = 1; i <= n; i++)
        {
            if(!visited[i] && cap[v][i] > 0) // if not visited yet
            {
                q.push(i);   // try to visit
                path[i] = v;
                visited[i] = true;
            }
        }
    }
    return false; // couldnt reach end
}

int solve(int beg, int end) {

    for(int i = 0; i <= n; ++i)
         for(int j = 0; j <= n; ++j)
            cap[i][j] = cap_orig[i][j];

    int max_flow=0;

    while(bfs(beg, end)) // when path is possible
    {
        int flow = HUGE, p, v;

        v = end;
        while(v != beg){ // trace back the path & get flow
            p = path[v];
            flow = min(flow,cap[p][v]);

            v = p;
        }

        v = end;
        //cerr << "path: ";
        while(v != beg){
            //cerr << v << " <- ";
            p = path[v];
            cap[p][v] -= flow;
            cap[v][p] += flow;

            v = p;
        }
        //cerr << beg <<"\n";
        //showflow();

        max_flow += flow;
    }

    return max_flow;
}



int main (){

    ios_base::sync_with_stdio(0);

    string line;
    int i, j, a, b;

    cin >> test;
    while(test--){
        cin >> n >> m;
        //cerr << "CASE " << n << " " << m << "\n";

        memset(graph,0,sizeof(graph));
        memset(cap_orig,0,sizeof(cap_orig));
        
        for(i = 0; i < m; ++i){
            cin >> line;
            sscanf(line.c_str(), "(%d,%d)", &a, &b);
            ++a,++b;
            //cerr << a << " " << b << "\n";
            graph[a].push_back(b);
            graph[b].push_back(a);
            cap_orig[a][b] = 1;
            cap_orig[b][a] = 1;
        }
        
        if(n*(n-1)/2 == m) { // full graph   
            cout << n << "\n";
            continue;
        } 
        if(m < n-1){ // surely disconnected
            cout << "0\n";
            continue;
        }
        /*for(i = 1; i <= n; ++i){
            if(graph[i].size() == n-1){ // single vertex
                cout << "1\n";
                continue;
            } 
        }*/
        
        int ans = n;

        for(i = 1; i <= n; ++i){
            for(j = i+1; j <= n; ++j){
                ans = min(ans, solve(i,j));
            }
        }

        cout << ans << "\n";
    }

    return 0;
}