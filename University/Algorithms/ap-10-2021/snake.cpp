#include <iostream>
#include <queue>
#include <cmath>

#define CUBESIZE 6
#define SIZE 100

using namespace std;

short paths[SIZE+1];

short solve(){
    short i, moves = 0, from = 1, to, limit;
    bool visited[SIZE+1] = {0};
    queue<short> q;

    visited[from] = true;
    q.push(from);
    q.push(moves);
    
    while(!q.empty()){
        from = q.front(); q.pop();
        moves = q.front(); q.pop();

        if(from == SIZE) return moves;

        limit = min(from+CUBESIZE, SIZE);
        for(i = from+1; i <= limit; ++i){
            if(visited[i]) continue;
            
            to = paths[i] == -1 ? i : paths[i];
            visited[to] = visited[i] = true;
            q.push(to);
            q.push(moves+1);
            //cerr << from << " -> " << to << "\n";
        }
    }

    // cannot reach end
    return -1;
}

int main (){

    ios_base::sync_with_stdio(0);
    short test, n, i, a, b;
    cin >> test;
    while(test--){
        //cerr << "--- TEST CASE ---\n";
        for(i = 1; i <= SIZE; ++i) paths[i] = -1;
        cin >> n;
        for(i = 0; i < n; ++i){
            cin >> a >> b;
            paths[a] = b;
        }
        cin >> n;
        for(i = 0; i < n; ++i){
            cin >> a >> b;
            paths[a] = b;
        }

        cout << solve() << "\n";
    }

    return 0;
}