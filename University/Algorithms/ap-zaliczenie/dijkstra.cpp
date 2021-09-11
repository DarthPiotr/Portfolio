#include <iostream>
#include <vector>
#include <queue>

#define SIZE 10

using namespace std;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

struct edge{ int to, weight; };
vector<edge> graph[SIZE];
int dst[SIZE], parent[SIZE];

void dijkstra(int s, int e) {
    int v,w;
    pii qe;
    for(int i = 0; i < SIZE; ++i) 
        dst[i] = 2'000'000,
        parent[i] = -1;
    priority_queue<pii> q;

    dst[s] = 0;
    q.push({0,s});
    while(!q.empty()){
        v = q.top().second;
        w = q.top().first; q.pop();
        cerr << v << "\n";

        for(auto u : graph[v]){
            if(dst[u.to] > dst[v] + u.weight){
                dst[u.to] = dst[v] + u.weight;
                parent[u.to] = v;
                q.push({dst[u.to], u.to});
            }
        }
    }
}

int main (){

    ios_base::sync_with_stdio(0);
    /*
    graph[1].push_back({6,14});
    graph[1].push_back({3,9});
    graph[1].push_back({2,7});
    graph[2].push_back({1,7});
    graph[2].push_back({3,10});
    graph[2].push_back({4,15});
    graph[3].push_back({1,9});
    graph[3].push_back({2,10});
    graph[3].push_back({4,11});
    graph[3].push_back({6,2});
    graph[4].push_back({2,15});
    graph[4].push_back({3,11});
    graph[4].push_back({5,6});
    graph[5].push_back({4,6});
    graph[5].push_back({6,9});
    graph[6].push_back({1,14});
    graph[6].push_back({3,2});
    graph[6].push_back({5,9});*/

    graph[1].push_back({2,1});
    graph[1].push_back({3,0});
    graph[2].push_back({3,1});
    graph[1].push_back({4,99});
    graph[4].push_back({2,-300});


    int a,b;
    cin >> a >> b;

    dijkstra(a, b);
    for(int i = 1; i <= 6; ++i)
        cout << i << " dst: " << dst[i] << "\n";

    for(int v = b; v != -1; v = parent[v])
        cout << v << " <- ";
    cout << "\b-\n";    

    return 0;
}