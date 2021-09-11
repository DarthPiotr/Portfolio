#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

struct node{
    long long sum, maxsum;
    long long maxleftsum, maxrightsum;
};

int n, m, base;
node* tree;

long long query(int beg, int end) {
    beg = beg - 1 + base;
    end = end + 1 + base;

    node left, right;

    cerr << "L: " << beg+1 << ", R: " << end-1 << "\n";
    left = tree[beg+1];
    right = tree[end-1];
    cerr << "\nLEFT: \n";
    cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
    cerr << "RIGHT: \n";
    cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n"; 
    beg /= 2; end /= 2;



    while(beg/2 != end/2){
        cerr << "L: " << beg+1 << ", R: " << end-1 << "\n";

        /*if(beg+1 == end-1){
            cerr << "Same. breaking\n";
            break;
        }*/
        //cerr << "last beg: " << lastb << ", last end: " << laste << "\n";
        if(beg % 2 == 0){ // jesli poczatek bedzie prawym synem
            // tree[beg+1] - wierzcholek ktory odwiedzamy
            cerr << "L ";
            left.maxsum = max(max(left.maxrightsum + tree[beg+1].maxleftsum, left.maxsum), tree[beg+1].maxsum);
            left.maxleftsum = max(left.maxleftsum, left.sum + tree[beg+1].maxleftsum);
            left.maxrightsum = max(tree[beg+1].maxrightsum, tree[beg+1].sum + left.maxrightsum);
            left.sum += tree[beg+1].sum;
            left.maxsum = max(left.maxsum, left.sum);   
             
            //cerr << "beg new res => " << left.maxsum << "\n";
        }

        if(end % 2 == 1){ // jesli koniec bedzie lewym synem
            cerr << "R";
            right.maxsum = max(max(right.maxleftsum + tree[end-1].maxrightsum, right.maxsum), tree[end-1].maxsum);
            right.maxrightsum = max(right.maxrightsum, right.sum + tree[end-1].maxrightsum);
            right.maxleftsum = max(tree[end-1].maxleftsum, tree[end-1].sum + right.maxleftsum);
            right.sum += tree[end-1].sum;
            right.maxsum = max(right.maxsum, right.sum);
             
            //cerr << "beg new res => " << left.maxsum << "\n";

        }

        cerr << "\nLEFT: \n";
        cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
        cerr << "RIGHT: \n";
        cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n"; 

        beg /= 2;
        end /= 2;
    }

    long long sum = left.sum + right.sum;
    //int maxleftsum = max(left.maxleftsum, left.sum + right.maxleftsum);
    //int maxrightsum = max(right.maxrightsum, right.sum + left.maxrightsum);
    long long maxsum = max(max(max(sum, left.maxrightsum + right.maxleftsum), left.maxsum), right.maxsum); 

    //cerr << "FINAL Beg: " << beg << ", end: " << end << "\n";
    return maxsum;
}

void insert(int x, int v){
    int p = base+x;
    tree[p].maxsum = v;
    tree[p].sum = v;
    tree[p].maxleftsum = v;
    tree[p].maxrightsum = v;

    do {
        p = p / 2;
        tree[p].sum = tree[2*p].sum + tree[2*p+1].sum;
        tree[p].maxleftsum = max(tree[2*p].maxleftsum, tree[2*p].sum + tree[2*p+1].maxleftsum);
        tree[p].maxrightsum = max(tree[2*p+1].maxrightsum, tree[2*p+1].sum + tree[2*p].maxrightsum);
        tree[p].maxsum = max(max(max(tree[p].sum, tree[2*p].maxrightsum + tree[2*p+1].maxleftsum), tree[2*p].maxsum), tree[2*p+1].maxsum); 
    } while (p != 1);
}

int main (){

    ios_base::sync_with_stdio(0);

    int q, a, b, i;

    cin >> n;
    base = 1 << (int)ceil(log2(n));
    tree = new node[2*base];
    memset(tree, 0, sizeof(tree)*2*base);
    //cerr << "sizeof tree: " << sizeof(tree)*2*base << "\n";

    //cerr << "Base: " << base << "\n";

    for(i = 0; i < n; ++i){
        cin >> a;
        insert(i, a);
    }

    /*cerr << "tree:\n";
    for(i = 1; i < 2*base; ++i)
        cerr << "s: "<<tree[i].sum<<", mxsum: "<<tree[i].maxsum<<"\nrmax: "<<tree[i].maxrightsum<<"\nlmax: "<<tree[i].maxleftsum<<"\n"; 
*/
    cin >> m;

    while(m--){ 
        cin >> a >> b;
        cout << query(a-1, b-1) << "\n";
    }

    delete tree;

    return 0;
}

/*

16 
-1 2 3 1 5 -4 1 -8 9 -11 3 9 13 -14 1 7
1
2 15


==> 25
*/