#include <iostream>
#include <cmath>

using namespace std;

int n, r, base;
int* tree;

int query(int beg, int end){
    int res = 0;
    beg = beg - 1 + base;
    end = end + 1 + base;
    while(beg/2 != end/2){
        //cerr << "Beg: " << beg << ", end: " << end << "\n";
        if(beg % 2 == 0){ // jesli poczatek jest lewym synem
            res = max(res, tree[beg+1]);
        }
        if(end % 2 == 1){ // jesli koniec jest prawym synem
            res = max(res, tree[end-1]);
        }
        //cerr << "res: " << res << "\n";

        beg /= 2;
        end /= 2;
    }
    //cerr << "FINAL Beg: " << beg << ", end: " << end << "\n";
    return res;
}

void insert(int x, int v){
    int p = base+x;
    tree[p] = v;

    do {
        p = p / 2;
        tree[p] = max(tree[2*p], tree[2*p+1]);
    } while (p != 1);
}

int main (){

    ios_base::sync_with_stdio(0);

    int q, a, b, i;

    cin >> n >> r;
    base = 1 << (int)ceil(log2(n));
    tree = new int[2*base];

    //cerr << "Base: " << base << "\n";

    while(r--){ 
        cin >> q >> a >> b;
        switch(q){
            case 1:
                insert(a, b);
                /*for(i = 1; i < 2*n; ++i)
                    cerr << tree[i] << " ";
                cerr << "\n";*/
                break;
            default:
                cout << query(a, b) << "\n";
                break;
        }
    }

    delete tree;

    return 0;
}