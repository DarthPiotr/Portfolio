#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

typedef pair<short, short> pss;

struct field {
public:
    bool visited;
    int cost;

    field() : visited(true), cost(0) {}
    field(bool v, int c) : visited(v), cost(c) {}
}tab[2000][2000];

struct cmp {
    bool operator()(const pss& p1, pss& p2) {
        return p1.first + p1.second < p2.first + p2.second;
    }
};

short n, m;
int k;

void show() {
    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << (tab[i][j].visited ? 'X' : '.');
        }
        cout << "\n";
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    int i, j, bcost=0;
    char c;
    priority_queue<pss, vector<pss>, cmp> Q;

    cin >> n >> m >> k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> c;
            tab[i][j].visited = c == 'X';
        }
    }

    Q.push(pair<short, short>(0, 0));
    pss curr;
    while (Q.size() > 0) {
        curr = Q.top();
        Q.pop();
        i = curr.first;
        j = curr.second;

        if (tab[i][j].visited) continue;

        //cout << "(" << i << "," << j << ")\n";

        tab[i][j].visited = true;

        if (i + 1 < n) { // can down
            if (i + 2 == n && j+1 == m) {
                bcost = tab[i][j].cost;
                break;
            }

            if (!tab[i + 1][j].visited) {
                tab[i + 1][j].cost = tab[i][j].cost;
                Q.push(pss(i + 1, j));
            }
        }
        if (j + 1 < m) { // can right
            if (i+1 == n && j + 2 == m) {
                bcost = tab[i][j].cost;
                break;
            }

            if (!tab[i][j + 1].visited) {
                tab[i][j + 1].cost = tab[i][j].cost;
                Q.push(pss(i, j + 1));
            }
        }
        if (i - 1 >= 0) { // can up
            if (!tab[i - 1][j].visited) {
                tab[i - 1][j].cost = tab[i][j].cost + 1;
                Q.push(pss(i - 1, j));
            }
        }
        if (j - 1 >= 0) { // can left
            if (!tab[i][j - 1].visited) {
                tab[i][j - 1].cost = tab[i][j].cost + 1;
                Q.push(pss(i, j - 1));
            }
        }
    }

    //cout << "\nBcost: " << bcost << "\n";
    int cost = m+n-2, crnt;
    int min=INT32_MAX, mincnt=0;
    while(k--){
        cin >> i >> j;
        crnt = (cost+bcost)*i+bcost*j;
        if(crnt < min){
            min = crnt;
            mincnt=1;
        }
        else if(crnt == min) mincnt++;

    }
    cout << "B: " << bcost << "\n";
    cout << min << " " << mincnt << "\n"; 
    return 0;
}