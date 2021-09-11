#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

struct node{
    long long sum = 0, maxsum = -10001;
    long long maxleftsum = -10001, maxrightsum = -10001;
};

int n, m, base;
node* tree;

long long query(int beg, int end) {
    bool bswap = false, eswap = false;

    beg += base;
    end += base;

    cerr << "L: " << beg << ", R: " << end << "\n";
    if(beg == end){
        cerr << "Single cell\n";
        return tree[beg].maxsum;
    }

    node left, right;

    left = tree[beg];
    right = tree[end];
    cerr << "\nLEFT: \n";
    cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
    cerr << "RIGHT: \n";
    cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n"; 
    
    if(beg/2 != end/2){
        if(beg % 2 == 0){
            beg /= 2;
            left = tree[beg];
            bswap = true;
        }
        else{
            beg = beg/2 + 1;
        }
        if(end % 2 == 1){
            end /= 2;
            right = tree[end];
            eswap  =true;
        }
        else{
            end = end/2 - 1;
        }
    }



    while(beg/2 < end/2){
        cerr << "L: " << beg << ", R: " << end << "\n";

        /*if(beg == end){
            cerr << "Same. breaking\n";
            break;
        }*/
        //cerr << "last beg: " << lastb << ", last end: " << laste << "\n";
        if(beg % 2 == 1 && !bswap){ // jesli poczatek bedzie prawym synem
            // tree[beg] - wierzcholek ktory odwiedzamy
            cerr << "L ";
            left.maxsum = max(max(left.maxrightsum + tree[beg].maxleftsum, left.maxsum), tree[beg].maxsum);
            left.maxleftsum = max(left.maxleftsum, left.sum + tree[beg].maxleftsum);
            left.maxrightsum = max(tree[beg].maxrightsum, tree[beg].sum + left.maxrightsum);
            left.sum += tree[beg].sum;
            left.maxsum = max(left.maxsum, left.sum);   
             
            //cerr << "beg new res => " << left.maxsum << "\n";
        }

        if(end % 2 == 0 && !eswap){ // jesli koniec bedzie lewym synem
            cerr << "R";
            right.maxsum = max(max(right.maxleftsum + tree[end].maxrightsum, right.maxsum), tree[end].maxsum);
            right.maxrightsum = max(right.maxrightsum, right.sum + tree[end].maxrightsum);
            right.maxleftsum = max(tree[end].maxleftsum, tree[end].sum + right.maxleftsum);
            right.sum += tree[end].sum;
            right.maxsum = max(right.maxsum, right.sum);
             
            //cerr << "beg new res => " << left.maxsum << "\n";

        }

        cerr << "\nLEFT: \n";
        cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
        cerr << "RIGHT: \n";
        cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n"; 

        if(beg/2 < end/2){
            if(beg % 2 == 0){
                beg /= 2;
                left = tree[beg];
                bswap = true;
            }
            else{
                beg = beg/2 + 1;
                bswap = false;
            }
            if(end % 2 == 1){
                end /= 2;
                right = tree[end];
                eswap  =true;
            }
            else{
                end = end/2 - 1;
                eswap = false;
            }
        }
    }


        cerr << "===ENDING===\n";
        cerr << "L: " << beg << ", R: " << end << "\nLEFT:\n";
        cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
        cerr << "RIGHT: \n";
        cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n"; 



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

    //ios_base::sync_with_stdio(0);

    int q, a, b, i;

    cin >> n;
    base = 1 << (int)ceil(log2(n));
    tree = new node[2*base];
    memset(tree, 0xff, sizeof(tree)*2*base);
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
        cin >> q >> a >> b;
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