#include <iostream>
#include <vector>

using namespace std;

struct Node{
    bool processed = false;
    vector<Node*> children;
} tree[10001];

int N, M;

int DFS(Node* node){
    node->processed = true;

    if(node->children.size() == 0)
        return 1;

    int res = 0;
    for(auto n : node->children){
        if(!n->processed) res += DFS(n);
    }

    return res + 1;
}

int main (){

    ios_base::sync_with_stdio(0);

    int i, beg, end, res = 0;

    cin >> N >> M;

    // w drzewie liczba krawedzi to dokladnie N-1
    if(M != N - 1){
        cout << "NO\n";
        return 0;
    }

    for(i = 0; i < M; i++){
        cin >> beg >> end;
        tree[beg].children.push_back(&tree[end]);
        tree[end].children.push_back(&tree[beg]);
    }

    res = DFS(&tree[1]);

    cout << (res == N ? "YES\n" : "NO\n");

    return 0;
}