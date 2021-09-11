#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

char tab[1000][1000];
int dst[1000][1000];

short dx[4] = {1, 0, -1, 0};
short dy[4] = {0, 1, 0, -1};

int t, h, w;

void compute_distances(int& x, int& y, int& max_len){
    queue<int> q;
    int i, dst = 0, c_x, c_y;
    bool visited[1000][1000] = {0};

    visited[x][y] = true;

    for(i = 0; i < 4; ++i){
        if(x + dx[i] >= 0 && x + dx[i] < h && 
           y + dy[i] >= 0 && y + dy[i] < w){
             if(tab[x + dx[i]][y + dy[i]] == '.' &&!visited[x + dx[i]][y + dy[i]]){
                q.push(x + dx[i]);
                q.push(y + dy[i]);
                q.push(dst + 1);
                visited[x + dx[i]][y + dy[i]] = true;
            }  
        }
    }

    while(!q.empty()){
        c_x = q.front(); q.pop();
        c_y = q.front(); q.pop();
        dst = q.front(); q.pop();

        if(dst > max_len){
            x = c_x;
            y = c_y;
            max_len = dst;
        }

        for(i = 0; i < 4; ++i){
            if(c_x + dx[i] >= 0 && c_x + dx[i] < h && 
               c_y + dy[i] >= 0 && c_y + dy[i] < w){
                if(tab[c_x + dx[i]][c_y + dy[i]] == '.' && !visited[c_x + dx[i]][c_y + dy[i]]){
                    q.push(c_x + dx[i]);
                    q.push(c_y + dy[i]);
                    q.push(dst + 1);
                    visited[c_x + dx[i]][c_y + dy[i]] = true;
                }
            }  
        }
    }
}

int main (){

    ios_base::sync_with_stdio(0);

    int i, j, maxlen;
    
    int m_x, m_y;

    cin >> t;
    while(t--){
        cin >> w >> h;
        m_x = -1;
        maxlen = 0;

        for(i = 0; i < h; ++i){
            cin >> tab[i];
            if(m_x == -1){
                for(j = 0; j < w; ++j){
                    if(tab[i][j] == '.'){
                        m_x = i; m_y = j;
                    }
                }
            }
        }

        if(m_x == -1){
            cout << "Maximum rope length is 0.\n";
            continue;
        }

        memset(dst, 0, sizeof(dst));

        compute_distances(m_x, m_y, maxlen);
        compute_distances(m_x, m_y, maxlen);

        cout << "Maximum rope length is "<< maxlen <<".\n";

        /*for(i = 0; i < h; ++i) {
            for(j = 0; j < w; ++j) {
                cerr << tab[i][j];
            }
            cerr << "\n";
        }*/
    }

    return 0;
}