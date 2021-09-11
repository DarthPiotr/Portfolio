#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

#define MAX_EDGES 4'498'501
#define MAX_VERTICES 3001

using namespace std;

int n, m;

struct edge{
    edge() {};
    edge(short i, int w) : to(i), weight(w) {};
    short to;
    int weight;
} heap[MAX_EDGES];
int h_size = 0;

bool e_comp(const edge &e1, const edge &e2) { 
    return e1.weight > e2.weight; 
}

struct vert{
    //short index;
    vector<edge> edges;
} graph[3001];
bool visited[MAX_VERTICES] = {0};

void hpush(edge e){
    heap[h_size++] = e;
    push_heap(heap, heap+h_size, e_comp);

    /*cerr << "Push " << e.weight << "\n";
    for(int i = 0; i < h_size; ++i) cerr << heap[i].weight << " ";
    cerr << "\n";*/
}

edge hpop(){
    edge e = heap[0];
    pop_heap(heap, heap+h_size, e_comp);
    --h_size;

    /*cerr << "Pop (" << e.weight << ")\n";
    for(int i = 0; i < h_size; ++i) cerr << heap[i].weight << " ";
    cerr << "\n";*/

    return e;
}

int main (){
    ios_base::sync_with_stdio(0);
    
    long long result = 0;
    int w;
    short a, b;
    edge cur;

    cin >> n >> m;
    while(m--){
        cin >> a >> b >> w;
        //graph[a].index = a;
        //graph[b].index = b;
        graph[a].edges.push_back(edge(b, w));
        graph[b].edges.push_back(edge(a, w));
    }
    
    cin >> a;
    
    --n;
    while(n--){
        visited[a] = true;
        for(auto &e : graph[a].edges){
            if(!visited[e.to])
                hpush(e);
        }
        do{
            cur = hpop();
        } while(visited[cur.to]);
        result += cur.weight;
        //cerr << "Res: " << result << "\n";
        a = cur.to;
    }

    cout << result << "\n";

    return 0;
}