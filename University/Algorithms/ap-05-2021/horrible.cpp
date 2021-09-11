#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

//#define __DEBUG__
#define SIZE 262150

using namespace std;
typedef long long ll;

int n, q, t, base;
ll tree[SIZE] = {0};
ll lazy[SIZE] = {0};

#ifdef __DEBUG__
int get_node_span(int node){
    int k = 0;
    while(node != 0)
        node = node >> 1, ++k;
    return base >> k;
}
void displayTree(long long (&tab)[SIZE]){
    int cnt = 2;
    int begspace = base;
    for(int j = 0; j < base - cnt-1; ++j) cerr << " ";
    for(int i = 1; i < 2*base; ++i){
        cerr << tab[i];
        for(int j = 0; j < (begspace<<1)-1; ++j) cerr << " ";
        if(i == cnt-1){
            cerr << "\n";
            for(int j = 0; j < (begspace>>1)-1; ++j) cerr << " ";
            cnt = cnt << 1;
            begspace = begspace >> 1;
        }
    }
}
#endif

/*int query(int beg, int end){
    long long res = 0;
    beg = beg - 1 + base;
    end = end + 1 + base;
    while(beg/2 != end/2){
        if(beg % 2 == 0){ // jesli poczatek jest lewym synem
            res += tree[beg+1];
        }
        if(end % 2 == 1){ // jesli koniec jest prawym synem
            res += tree[end-1];
        }

        beg /= 2;
        end /= 2;
    }
    return res;
}*/

void update(int query_l, int query_r, int val, int node, int node_l, int node_r){
    // node in not withing update range at all
    if(query_l > node_r || query_r < node_l) return;

    // query is less than node span on at least one side
    if(query_l > node_l || query_r < node_r) {
        int mid = (node_l + node_r) / 2; // get chidlren spans
        //update children
        update(query_l, query_r, val, 2*node,  node_l, mid);
        update(query_l, query_r, val, 2*node+1, mid+1, node_r);

        tree[node] = tree[2*node] + tree[2*node+1]      // sum of its children
                + (mid - node_l + 1) * lazy[2*node]     // value of child's update * child's span
                + (node_r - mid) * lazy[2*node+1];      // same for the second child
    }
    else { 
        // query is equal to or larger than node span (node fully inside query)
        lazy[node] += val;
    }
}

ll query (int query_l, int query_r, int node, int node_l, int node_r){
    // node not withing query at all
    if(query_l > node_r || query_r < node_l) return 0;

    // find common part of query and node
    int beg = max(query_l, node_l),
        end = min(query_r, node_r);
    ll res = (end-beg+1) * lazy[node]; // common part length * update value

    // query is less than node span on at least one side
    if(query_l > node_l || query_r < node_r) {
        int mid = (node_l + node_r) / 2; // get children spans

        // query the children
        res += query(query_l, query_r, 2*node, node_l, mid);
        res += query(query_l, query_r, 2*node+1, mid+1, node_r);
    }
    else { 
        // query is equal to or larger than node span (node fully inside query)
        res += tree[node]; // add current sum of subtree
    }

    return res;
}

int main (){

    //ios_base::sync_with_stdio(0);
    int x, a, b, y;

    cin >> t;
    while (t--){
        cin >> n >> q;
        base = 1 << (int)ceil(log2(n));
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));

        while(q--){
            cin >> x; 
            if (x){
                cin >> a >> b;
                cout << query(a-1, b-1, 1, 0, n-1) << "\n";
            }
            else{
                cin >> a >> b >> y;
                update(a-1, b-1, y, 1, 0, n-1);
            }
#ifdef __DEBUG__
            cerr << "Query: " << (x ? "read" : "write") << " " << a << " " << b << (x ? "" : " +"+to_string(y)) << "\n";
            cerr << "Tree:\n "; displayTree(tree);
            cerr << "\n\nLazy:\n "; displayTree(lazy);
            cerr << "\n";
#endif
        }
    }

    return 0;
}// XDDD
