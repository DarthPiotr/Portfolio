#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int n, q, t, base;
long long tree[262150] = {0};

int query(int beg, int end){
    long long res = 0;
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

void add(int beg, int end, int val){
    int p;
    while(beg <= end){
        p = base+beg;
        tree[p] += val;
        do{
            p /= 2;
            tree[p] = tree[2*p] + tree[2*p+1];
        }while(p != 1);
        ++beg;
    }
}

int main (){

    //ios_base::sync_with_stdio(0);
    int x, a, b, y;

    cin >> t;
    while (t--){
        cin >> n >> q;
        base = 1 << (int)ceil(log2(n));
        memset(tree, 0, sizeof(tree));

        while(q--){
            cin >> x; 
            if (x){
                cin >> a >> b;
                cout << query(a-1, b-1) << "\n";
            }
            else{
                cin >> a >> b >> y;
                add(a-1, b-1, y);
            }

            /*cerr << "Query: " << (x ? "read" : "write") << " " << a << " " << b << "\n";
            cerr << "Tree:\n ";
            int cnt = 2;
            int begspace = base;
            for(int j = 0; j < base - cnt; ++j) cerr << " ";
            for(int i = 1; i < 2*base; ++i){
                cerr << tree[i];
                for(int j = 0; j < (begspace<<1)-1; ++j) cerr << " ";
                if(i == cnt-1){
                    cerr << "\n";
                    for(int j = 0; j < (begspace>>1)-1; ++j) cerr << " ";
                    cnt = cnt << 1;
                    begspace = begspace >> 1;
                }
            }
            cerr << "\n\n";*/
        }
    }

    return 0;
}