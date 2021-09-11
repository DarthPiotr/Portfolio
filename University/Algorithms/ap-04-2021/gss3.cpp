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
    int nbeg, nend;
    long long sum, maxsum;

    beg += base;  // new indices
    end += base;

    //cerr << "L: " << beg << ", R: " << end << "\n";
    if(beg == end){     // in case it's a single cell
        //cerr << "Single cell\n";
        return tree[beg].maxsum;
    }

    node left, right;

    left = tree[beg];
    right = tree[end];
    /*cerr << "\nLEFT: \n";
    cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
    cerr << "RIGHT: \n";
    cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n"; 
    */
    
    // jumping to the next node

    while(beg < end){
        // get possible next positions
        if(beg%2 == 0)  // beg is left node
            nbeg = beg/2;
        else            // beg is right node
            nbeg = beg/2+1;

        if(end%2 == 0)  // end is left node
            nend = end/2-1;
        else            // end is right node
            nend = end/2;
       /* cerr << "L: " << nbeg << ", R: " << nend << "\n";
        cerr << "\nLEFT: \n";
        cerr << "s: "<<left.sum<<", mxsum: "<<left.maxsum<<"\nrmax: "<<left.maxrightsum<<"\nlmax: "<<left.maxleftsum<<"\n"; 
        cerr << "RIGHT: \n";
        cerr << "s: "<<right.sum<<", mxsum: "<<right.maxsum<<"\nrmax: "<<right.maxrightsum<<"\nlmax: "<<right.maxleftsum<<"\n\n";
*/
        if(nbeg < nend){ // they dont point into the same node
           // cerr << "Standard operation upwards\n";
            if(beg%2 == 0){ // beg was left child
                //left = tree[nbeg]; // override
                left.maxsum = max(max(left.maxrightsum + tree[beg+1].maxleftsum, left.maxsum), tree[beg+1].maxsum);
                left.maxleftsum = max(left.maxleftsum, left.sum + tree[beg+1].maxleftsum);
                left.maxrightsum = max(tree[beg+1].maxrightsum, tree[beg+1].sum + left.maxrightsum);
                left.sum += tree[beg+1].sum;
                left.maxsum = max(left.maxsum, left.sum);
            }
            else{  // beg was right child
                // recalculate left
                left.maxsum = max(max(left.maxrightsum + tree[nbeg].maxleftsum, left.maxsum), tree[nbeg].maxsum);
                left.maxleftsum = max(left.maxleftsum, left.sum + tree[nbeg].maxleftsum);
                left.maxrightsum = max(tree[nbeg].maxrightsum, tree[nbeg].sum + left.maxrightsum);
                left.sum += tree[nbeg].sum;
                left.maxsum = max(left.maxsum, left.sum);
            }

            if(end%2 == 1){ // end was odd
                //right = tree[nend]; // override
                // recalculate right
                right.maxsum = max(max(right.maxleftsum + tree[end-1].maxrightsum, right.maxsum), tree[end-1].maxsum);
                right.maxrightsum = max(right.maxrightsum, right.sum + tree[end-1].maxrightsum);
                right.maxleftsum = max(tree[end-1].maxleftsum, tree[end-1].sum + right.maxleftsum);
                right.sum += tree[end-1].sum;
                right.maxsum = max(right.maxsum, right.sum);
            }
            else{ // end was left child
                // recalculate right
                right.maxsum = max(max(right.maxleftsum + tree[nend].maxrightsum, right.maxsum), tree[nend].maxsum);
                right.maxrightsum = max(right.maxrightsum, right.sum + tree[nend].maxrightsum);
                right.maxleftsum = max(tree[nend].maxleftsum, tree[nend].sum + right.maxleftsum);
                right.sum += tree[nend].sum;
                right.maxsum = max(right.maxsum, right.sum);

            }
        }
        else if(nbeg == nend){ // pointing to the same node
            if(beg + 1 == end){ // children of the same parent
             //   cerr << "Children of same parent\n";
                // compare both
                sum = left.sum + right.sum;
                maxsum = max(max(max(sum, left.maxrightsum + right.maxleftsum), left.maxsum), right.maxsum);

                return maxsum; // result is in this parent
            }
            else if(nbeg*2 == beg){ // beg was child of nbeg, but end wasn't
             //   cerr << "Beg was child, end jumped\n";
                //left = tree[nbeg]; // override left
                left.maxsum = max(max(left.maxrightsum + tree[beg+1].maxleftsum, left.maxsum), tree[beg+1].maxsum);
                left.maxleftsum = max(left.maxleftsum, left.sum + tree[beg+1].maxleftsum);
                left.maxrightsum = max(tree[beg+1].maxrightsum, tree[beg+1].sum + left.maxrightsum);
                left.sum += tree[beg+1].sum;
                left.maxsum = max(left.maxsum, left.sum);

                // compare with right
                sum = left.sum + right.sum;
                //int maxleftsum = max(left.maxleftsum, left.sum + right.maxleftsum);
                //int maxrightsum = max(right.maxrightsum, right.sum + left.maxrightsum);
                maxsum = max(max(max(sum, left.maxrightsum + right.maxleftsum), left.maxsum), right.maxsum); 

                return maxsum; // return max
            }
            else if(nend*2 + 1 == end){ // end was the child of nend, but beg wasn't
            //    cerr << "End was child, beg jumped\n";
                // recalculate right
                right.maxsum = max(max(right.maxleftsum + tree[end-1].maxrightsum, right.maxsum), tree[end-1].maxsum);
                right.maxrightsum = max(right.maxrightsum, right.sum + tree[end-1].maxrightsum);
                right.maxleftsum = max(tree[end-1].maxleftsum, tree[end-1].sum + right.maxleftsum);
                right.sum += tree[end-1].sum;
                right.maxsum = max(right.maxsum, right.sum);

                // compare with left
                sum = left.sum + right.sum;
                //int maxleftsum = max(left.maxleftsum, left.sum + right.maxleftsum);
                //int maxrightsum = max(right.maxrightsum, right.sum + left.maxrightsum);
                maxsum = max(max(max(sum, left.maxrightsum + right.maxleftsum), left.maxsum), right.maxsum);
                return maxsum; // return max
            }
            else{ // none was the child
             //   cerr << "Both jumped\n";
                // shift begin by comparing
                left.maxsum = max(max(left.maxrightsum + tree[nbeg].maxleftsum, left.maxsum), tree[nbeg].maxsum);
                left.maxleftsum = max(left.maxleftsum, left.sum + tree[nbeg].maxleftsum);
                left.maxrightsum = max(tree[nbeg].maxrightsum, tree[nbeg].sum + left.maxrightsum);
                left.sum += tree[nbeg].sum;
                left.maxsum = max(left.maxsum, left.sum);

                // compare with right
                sum = left.sum + right.sum;
                //int maxleftsum = max(left.maxleftsum, left.sum + right.maxleftsum);
                //int maxrightsum = max(right.maxrightsum, right.sum + left.maxrightsum);
                maxsum = max(max(max(sum, left.maxrightsum + right.maxleftsum), left.maxsum), right.maxsum); 

                return maxsum; // return max
            }
          //  cerr << "You shouldn't be here! Something went wrong... (inside)\n";
        }
        else{ // nbeg > nend
       //     cerr << "Both wanted to jump into invalid positions\n";
            // compare current left and right
            sum = left.sum + right.sum;
            //int maxleftsum = max(left.maxleftsum, left.sum + right.maxleftsum);
            //int maxrightsum = max(right.maxrightsum, right.sum + left.maxrightsum);
            maxsum = max(max(max(sum, left.maxrightsum + right.maxleftsum), left.maxsum), right.maxsum);
            return maxsum; // return max
        }
        beg = nbeg;
        end = nend;
    }
  //  cerr << "You shouldn't be here! Something went wrong... (returning)\n";
    return -696969;
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
        switch(q){
            case 1:
                cout << query(a-1, b-1) << "\n";
                break;
            default:
                insert(a-1, b);
                break;
        }
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