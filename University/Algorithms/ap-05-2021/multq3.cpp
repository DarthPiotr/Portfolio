#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int n, q, base;
int tree[263000] = {0};
int values[100001] = {0};

int query(int beg, int end){
    int res = 0;
    beg = beg - 1 + base;
    end = end + 1 + base;
    while(beg/2 != end/2){
        //cerr << "Beg: " << beg << ", end: " << end << "\n";
        if(beg % 2 == 0){ // jesli poczatek jest lewym synem
            res += tree[beg+1];
        }
        if(end % 2 == 1){ // jesli koniec jest prawym synem
            res += tree[end-1];
        }
        //cerr << "res: " << res << "\n";

        beg /= 2;
        end /= 2;
    }
    //cerr << "FINAL Beg: " << beg << ", end: " << end << "\n";
    return res;
}

void increment(int beg, int end){
    int p;
    while(beg <= end){
        p = base+beg;
        values[beg]++;
        tree[p] = values[beg] % 3 == 0 ? 1 : 0;
        do{
            p /= 2;
            tree[p] = tree[2*p] + tree[2*p+1];
        }while(p != 1);
        ++beg;
    }
}

int main (){

    //ios_base::sync_with_stdio(0);
    int x, a, b;
    cin >> n >> q;
    base = 1 << (int)ceil(log2(n));
    
    // init
    a = 0;
    while(a < n){
        b = base+a;
        tree[b] = 1;
        do{
            b /= 2;
            tree[b] = tree[2*b] + tree[2*b+1];
        }while(b != 1);
        ++a;
    }


    while(q--){
        cin >> x >> a >> b;
        if (x) cout << query(a, b) << "\n";
        else increment(a, b);
    }

    return 0;
}