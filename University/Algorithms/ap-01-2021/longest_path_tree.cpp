#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{
    int id;
    bool processed = false;
    vector<Node*> children;
} tree[10001];
int N;

int findLongestPath(Node* node, int depth, int* max){
    //for(int i = 0; i < depth; ++i) cout << " ";
    //cout << "Processing: " << node->id << "\n";
    
    if(node->children.size() == 0)
        return 1;
    
    int l1 = 0, l2 = 0, res;
    ++depth;
    node->processed = true;
    for(auto n : node->children){
        if(!n->processed){
            res = findLongestPath(n, depth, max) + 1;

            if(res > l1) l1 = res;
            else if(res > l2) l2 = res;  
        }
    }
    //for(int i = 0; i < depth; ++i) cout << " ";
    //cout << "l1: " << l1 << ", l2: " << l2 << "\n";


    res = l1 + l2;
    if(res > *max)
        *max = res;

    return l1;
}

int main (){

    ios_base::sync_with_stdio(0);

    int i, beg, end, max = 0;

    cin >> N;
    for(i = 1; i < N; ++i){
        cin >> beg >> end;
        tree[beg].id = beg;
        tree[end].id = end;
        tree[beg].children.push_back(&tree[end]);
        tree[end].children.push_back(&tree[beg]);
    }

    findLongestPath(&tree[1], 0, &max);
    cout << max << "\n";

    return 0;
}