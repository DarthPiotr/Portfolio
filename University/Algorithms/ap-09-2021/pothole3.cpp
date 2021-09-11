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
bool bfs() { // check if any paths are possible
    bool visited[SIZE] = {0};
    int v;
    memset(path, 0, sizeof(path));
	queue<int> q;

	q.push(1);  // start from 1
	path[1]=-1; // which has no parent

	while(!q.empty())
	{
		v = q.front(), q.pop();

		if(v == n) return true; // finish -> can get to the end

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

int solve() {
	int max_flow=0;

	while(bfs()) // when path is possible
	{
		int flow = HUGE, p, v;

        v = n;
        while(v != 1){ // trace back the path & get flow
            p = path[v];
			flow = min(flow,cap[p][v]);

            v = p;
        }

		v = n;
        cerr << "path: ";
        while(v != 1){
            cerr << v << " <- ";
            p = path[v];
            cap[p][v] -= flow;
            cap[v][p] += flow;

            v = p;
        }
        cerr << "1\n";
        showflow();

		max_flow += flow;
	}

	return max_flow;
}

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