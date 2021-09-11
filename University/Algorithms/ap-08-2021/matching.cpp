#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

#define SIZE 100'002

using namespace std;

int n, m, total, p;
// <1..n> - A part     <n+1..total> - B part
vector<int> graph[SIZE];
bool visited[SIZE];
map<int, int> match;

bool findmatch(int v){
    //cerr << "[FINDMATCH] Called with v=" << v << "\n";
    for(auto it = graph[v].begin(); it != graph[v].end(); ++it) { // checks every element connected to v
        // i is unvisited
        if(!visited[*it]){
            visited[*it] = true; // visit
            // try to find (new) match to i (elongate the path) - dont if i is not matched (-1)
            if(match[*it] == -1 || findmatch(match[*it])){ // if successfully found path or cannot match
                // it a new match
                match[*it] = v;
                match[v] = *it;
                // return successfull match
                return true;
            }
        }
    }
    return false;
}

int solve(){
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        // reset visited
        memset(visited, 0, sizeof(visited));
        // if can match i to anything, increment
        if(findmatch(i)) ++ans;

        /*cerr << "Solved for i=" << i << "\n";
        for (int j = 1; j <= total; j++) {
            cerr << j << " : " << match[j] << "\n";
            if(j == n) cerr << "------\n";
        }*/
    }
    return ans;
}

int main (){
    ios_base::sync_with_stdio(0);

    int a, b;    

    cin >> n >> m >> p;
    total = n+m;
    for(a = 0; a <= total; ++a) match[a] = -1;
    while(p--) {
        cin >> a >> b;
        graph[a].push_back(b+n);
        graph[b+n].push_back(a);
    }
    /*cerr << "GRAPH:\n";
    for(a = 0; a <= total; ++a){
        cerr << a << " -> ";
        for(auto it = graph[a].begin(); it != graph[a].end(); ++it){
            cerr << *it << " ";
        }
        cerr << "\n";
    }
    cerr << "\n";*/

    cout << solve() << "\n";

    return 0;
}