#include <iostream>
#include <string>

using namespace std;

struct field {
public:
    bool visited;
    int cost;

    field() : visited(true), cost(0) {}
    field(bool v, int c) : visited(v), cost(c) {}
}tab[2000][2000];

struct coords {
    short x, y;
    int cost = 0;
    coords(){}
    coords(short x, short y) : x(x), y(y) {}
    bool operator < (const coords& a) {
        return cost < a.cost;
    }
    bool operator > (const coords& a) {
        return cost > a.cost;
    }
} h[4000000];
int hl=0;

short n, m;
int k;

// HEAP

void heapParent(int index) {
    if (index == 0)
        return;

    int parent = (index - 1) / 2;

    if (h[parent] > h[index]) {
        swap(h[parent], h[index]);
        heapParent(parent);
    }
}

void heapChildren(int index) {
    int child = 1 + index * 2;

    if (child >= hl)
        return;

    if (child + 1 < hl)
        if (h[child + 1] < h[child])
            child = child + 1;

    if (h[index] > h[child]) {
        swap(h[index], h[child]);
        heapChildren(child);
    }
}

void addHeap(short x, short y, int cost) {
    h[hl].x = x;
    h[hl].y = y;
    h[hl].cost = cost;
    heapParent(hl++);
}

coords popMax() {
    swap(h[0], h[--hl]);
    heapChildren(0);
    return h[hl];
}

// HEAP END

int main() {

    ios_base::sync_with_stdio(0);
    int i, j, bcost = 0;
    char c;

    cin >> n >> m >> k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> c;
            tab[i][j].visited = c == 'X';
        }
    }


    addHeap(0, 0, 0);
    coords curr;
    while (hl > 0) {
        curr = popMax();
        i = curr.x;
        j = curr.y;

        if (tab[i][j].visited) continue;

        tab[i][j].visited = true;

        if (i + 1 < n) { // can down
            if (i + 2 == n && j + 1 == m) {
                bcost = tab[i][j].cost;
                break;
            }

            if (!tab[i + 1][j].visited) {
                tab[i + 1][j].cost = tab[i][j].cost;
                addHeap(i + 1, j, tab[i + 1][j].cost);
            }
        }
        if (j + 1 < m) { // can right
            if (i + 1 == n && j + 2 == m) {
                bcost = tab[i][j].cost;
                break;
            }

            if (!tab[i][j + 1].visited) {
                tab[i][j + 1].cost = tab[i][j].cost;
                addHeap(i, j + 1, tab[i][j + 1].cost);
            }
        }
        if (i - 1 >= 0) { // can up
            if (!tab[i - 1][j].visited) {
                tab[i - 1][j].cost = tab[i][j].cost + 1;
                addHeap(i - 1, j, tab[i - 1][j].cost);
            }
        }
        if (j - 1 >= 0) { // can left
            if (!tab[i][j - 1].visited) {
                tab[i][j - 1].cost = tab[i][j].cost + 1;
                addHeap(i , j - 1, tab[i][j - 1].cost);
            }
        }
    }

    int cost = m + n - 2, crnt;
    int min = INT32_MAX, mincnt = 0;
    while (k--) {
        cin >> i >> j;
        crnt = (cost + bcost) * i + bcost * j;
        if (crnt < min) {
            min = crnt;
            mincnt = 1;
        }
        else if (crnt == min) mincnt++;

    }
    cout << min << " " << mincnt << "\n";
    return 0;
}