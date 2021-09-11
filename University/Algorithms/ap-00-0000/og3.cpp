#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node{
    vector <int> son;
};

Node tree[10001];
bool* visited; //array of visited nodes
int max_path;

int BFS(int v, int& max_path, int n) //v - index of starting node
{
    int i, max_index = 0;
    queue <int> q;
    vector <int>::iterator it_son;
    int path[10001];

    for(i = 0; i <= n; i++)
    {
        path[i] = 0;
        visited[i] = false;
    }

    visited[v] = true;
    q.push(v);
    while(!q.empty())
    {
        v = q.front(); //index of node
        //cout << v << " ";
        q.pop(); //erase it
        //mark all sons of v
        cout << "visited " << v << "; checking children...\n";
        for(it_son = tree[v].son.begin(); it_son != tree[v].son.end(); it_son++)
        {
            if(visited[*it_son] == false && *it_son != 0)
            {
                q.push(*it_son);
                visited[*it_son] = true;
                path[*it_son] = path[v] + 1; //extend new path by one from father's index
                cout << "visited " << *it_son << "\n";
                cout << "setting path to " << *it_son << " as " << path[v]+1 << "\n";
            }
        }
    }

    for(i = 0; i <= n; i++)
    {
        if(path[i] > max_path) //nie musze pisac *, bo kod sam sobie max_path ustawia jako wskaznik
        {
            max_path = path[i];
            max_index = i;
        }
    }
    return max_index;
}



int main ()
{
    /*drzewo - nieskierowany, spojny graf acykliczny
    warunki:
    - wierzcholki - krawedzie == 1
    - graf spojny - sprawdzam DFSem*/

int i, n, a, b;
bool zm;
while(cin >> n)
{
        visited = new bool[n + 1];

        for(i = 0; i < n - 1; i++)
        {
            cin >> a >> b;
            //undirected tree
            tree[a].son.push_back(b);
            tree[b].son.push_back(a);
        }

        max_path = 0;
        cout << "BFS 1:\n";
        int bfs1 = BFS(1, max_path, n);
        cout << "bfs1 returned: " << bfs1 << ", maxpath: " << max_path <<"\n";
        cout << "------\nBFS 2:\n";
        int bfs2 = BFS(bfs1, max_path, n);
        cout << "bfs2 returned: " << bfs2  << ", maxpath: " << max_path <<"\n\n";
        cout << max_path;

        delete [] visited;
}


return 0;
}