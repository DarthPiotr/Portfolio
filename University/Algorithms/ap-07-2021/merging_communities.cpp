#include <iostream>

#define TAB_SIZE 100'001

using namespace std;

int n, q;

int parent[TAB_SIZE] = {0};
int csize[TAB_SIZE] = {0};

int find(int a){
    if(a == parent[a]) return a;

    return parent[a] = find(parent[a]);
}

void unite(int a, int b){
    a = find(a), b = find(b);
    if(a != b){
        if(csize[a] < csize[b]) swap(a, b);

        csize[a] += csize[b];
        parent[b] = parent[a];
    }
}

int main (){

    ios_base::sync_with_stdio(0);
    char c;
    int a, b, i;

    cin >> n >> q;

    for(i = 1; i <= n; ++i){
        parent[i] = i;
        csize[i] = 1;
    }

    while(q--){
        cin >> c;
        if(c == 'M') {
            cin >> a >> b;
            unite(a, b);
        }
        else {
            cin >> a;
            cout << csize[find(a)] << "\n";
        }
    }

    return 0;
}