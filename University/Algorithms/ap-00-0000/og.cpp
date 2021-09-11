#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int tab[21][21];
int dirty[11][11]; //index of dirty place and its coordinates
bool visited[21][21];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
int i, j;

struct Start{
    int x;
    int y;
};
Start v[11];


void BFS(int w, int l, int index) //index - starting index
{
    cout << index << " tu\n";
    queue <int> q;
    int path[30][30];
    int x2, y2;

    for(i = 1; i <= l; i++)
    {
        for(j = 1; j <= w; j++)
        {
            path[i][j] = 0;
            visited[i][j] = false;
        }
    }

    visited[v[index].y][v[index].x] = true;
    q.push(v[index].y);
    q.push(v[index].x);

    while(!q.empty())
    {
        v[index].y = q.front();
        q.pop(); //erase it
        v[index].x = q.front();
        q.pop();

        //neighbours
        for(i = 0; i < 4; i++) //4 directions
        {
            x2 = v[index].x + dx[i];
            y2 = v[index].y + dy[i];
            if((tab[y2][x2] == 1 || tab[y2][x2] == 2)&& visited[y2][x2] == false)
            {
                visited[y2][x2] = true;
                q.push(y2);
                q.push(x2);
                path[y2][x2] = path[v[index].y][v[index].x] + 1;
                if(tab[y2][x2] == 2) //dirty place or robot
                {
                    if(dirty[index][] > path[y2][x2])
                    {
                        dirty[index][] = path[y2][x2];
                        dirty[][index] = path[y2][x2];
                    }

                }
            }
        }
    }
}

int main ()
{
int w, l, amount, zm;
char n;
while(cin >> w >> l)
{
    if(w == 0 && l == 0) return 0;
    amount = 1;
    for(i = 1; i <= l; i++)
    {
        for(j = 1; j <= w; j++)
        {
            cin >> n;
            if(n == '.') //paths
            {
                tab[i][j] = 1;
            }
            else if(n == 'o' || n == '*')
            {
                tab[i][j] = 2;
                if(n == 'o')
                {
                    v[0].y = i;
                    v[0].x = j;

                }
                if(n == '*') //destinations
                {
                    v[amount].y = i;
                    v[amount].x = j;
                    amount++;
                }
            }
            else //obstacle
            {
                tab[i][j] = 0;
            }
        }
    }

    for(i = 0; i < amount; i++)
    {
        for(j = 0; j < amount; j++)
        {
            dirty[i][j] = 100;
        }
    }

    cout << amount << "\n";
    for(zm = 0; zm < amount; zm++)
    {
        //cout << v[zm].y << " " <<v[zm].x << "\n";
        BFS(w, l, zm);

    }

}


return 0;
}