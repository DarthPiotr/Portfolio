#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
int t, n, m;
char map[183][183];
int res[183][183];

short dx[4] = {1, 0, -1, 0};
short dy[4] = {0, 1, 0, -1};

int main (){

    ios_base::sync_with_stdio(0);

    int i, j;
    int x, y, dst;

    cin >> t;
    while(t--){
        cin >> n >> m;

        queue<int> q;
        memset(res, 0, sizeof(res));

        for(i = 0; i < n; ++i){
            for(j = 0; j < m; ++j){
                cin >> map[i][j];
                if(map[i][j] == '1'){
                    q.push(i);
                    q.push(j);
                    q.push(0);
                    map[i][j] = '2';
                }
            }
        }

        /*for(i = 0; i < n; ++i){
            for(j = 0; j < m; ++j){
                cerr << map[i][j] << " ";
            }
            cerr << "\n";
        }*/

        while(!q.empty()){
            x   = q.front(); q.pop();
            y   = q.front(); q.pop();
            dst = q.front(); q.pop();

            //cerr << "("<<x<<","<<y<<")\n";

            if(res[x][y] == 0)
                res[x][y] = dst;
            else if(dst < res[x][y])
                res[x][y] = dst;

            for(i = 0; i < 4; ++i){
                if(x + dx[i] >= 0 && x + dx[i] < n && 
                   y + dy[i] >= 0 && y + dy[i] < m){
                    if(map[x + dx[i]][y + dy[i]] != '2'){
                        //cerr << " ===> ("<<x + dx[i]<<","<<y + dy[i]<<")\n";
                        q.push(x + dx[i]);
                        q.push(y + dy[i]);
                        q.push(dst+1);
                        map[x + dx[i]][y + dy[i]] = '2';
                    }
                }
            }
        }

        for(i = 0; i < n; ++i){
            for(j = 0; j < m; ++j){
                cout << res[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}