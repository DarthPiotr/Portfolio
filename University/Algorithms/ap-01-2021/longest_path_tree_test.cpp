#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Node{
    int id;
    int maxPath = 0;
    vector<Node*> children;
} tree[10001];
bool processed[10001];
int N;

int findLongestPath(Node* node, int depth){   
    if(node->children.size() == 0)
        return depth;
    
    int res, max = 0;
    ++depth;
    processed[node->id] = true;
    for(auto n : node->children){
        if(!processed[n->id]){
            res = findLongestPath(n, depth) + 1;
            if(res > max) max = res;
        }
    }
    //for(int i = 0; i < depth; ++i) cout << " ";
    //cout << "Processing: " << node->id << "; max: " << max << "\n";

    return max;
}

int main (){

    ios_base::sync_with_stdio(0);

    int i, beg, end, max = 0, tmp;

    cin >> N;
    for(i = 1; i < N; ++i){
        cin >> beg >> end;
        tree[beg].id = beg;
        tree[end].id = end;
        tree[beg].children.push_back(&tree[end]);
        tree[end].children.push_back(&tree[beg]);
    }

    for(i = 1; i <= N; ++i){
        memset(processed, false, sizeof(processed));
        tmp = findLongestPath(&tree[i], 0);
        if(tmp > max) max = tmp;
    }
    cout << max << "\n";

    return 0;
}