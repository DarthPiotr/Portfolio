#include <iostream>

using namespace std;

// Node is defined as :
/*struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
};
*/
int getHeight(node *n){
    //cerr << "Height of " << (n != NULL ? n->val : 0) << " is " << (n != NULL ? n->ht : 0) << "\n"; 
    return n != NULL ? n->ht : 0;
}

int newHeight(node *n){
    if(n->left == NULL && n->right == NULL) return 0;
    return max(
        getHeight(n->left),
        getHeight(n->right)
    ) + 1;
}

int balance(node *n){
    if (n->left == NULL) return -(getHeight(n->right)+1);
    if (n->right == NULL) return getHeight(n->left)+1;
    return getHeight(n->left) - getHeight(n->right);
}

void debug(node* n){
    if(n != NULL){
        cerr << n->val << "(ht="<<n->ht<<",bf="<<balance(n)<<"){";
        cerr << "l:"; debug(n->left);
        cerr << "r:"; debug(n->right);
        cerr << "}";
    }
}

node* left(node* root){
    cerr << "left("<<root->val<<")\n";
    node* newroot = root->right;
    node* tmp = root->right->left;
    
    newroot->left = root;
    root->right = tmp;
    
    root->ht = newHeight(root);
    cerr << "New height of " << root->val << " is " << root->ht << "\n"; 
    newroot->ht = newHeight(newroot);
    cerr << "New height of " << newroot->val << " is " << newroot->ht << "\n"; 
    
    cerr << "newroot is " << newroot->val << "\n";
    { cerr << "DEBUG: "; debug(newroot); cerr << "\n"; }
    return newroot;
}

node* right(node* root){
    cerr << "right("<<root->val<<")\n";
    node* newroot = root->left;
    node* tmp = root->left->right;
    
    newroot->right = root;
    root->left = tmp;
    
    root->ht = newHeight(root);
    cerr << "New height of " << root->val << " is " << root->ht << "\n"; 
    newroot->ht = newHeight(newroot);
    cerr << "New height of " << newroot->val << " is " << newroot->ht << "\n";
    
    cerr << "newroot is " << newroot->val << "\n";
    { cerr << "DEBUG: "; debug(newroot); cerr << "\n"; }
    return newroot;
}

node * insert(node * root,int val)
{
    cerr << "insert("<<(root == NULL ? 0 : root->val)<<", "<<val<<"); ht="<<(root == NULL ? 0 : root->ht)<<"\n";
    
    if (root == NULL){
        struct node* n = new struct node();
        n->val = val;
        n->left = n->right = NULL;
        n->ht = 0;
        return n;
    }
    
    if(root->val == 3) { cerr << "DEBUG: "; debug(root); cerr << "\n"; }
    
    if(val < root->val){
        root->left  = insert(root->left,  val);
        cerr << "new left node: " << root->val << " -> " << root->left->val << "\n";
    }
    else{
        root->right = insert(root->right, val);
        cerr << "new right node: " << root->val << " -> " << root->right->val << "\n";
    }
    
    root->ht = max(
        getHeight(root->left),
        getHeight(root->right)
    ) + 1;
    cerr << "New height of " << root->val << " is " << root->ht << "\n"; 
    
    int bf = balance(root);
    cerr << "calculating bf for " << root->val << " = " << bf << "\n";
    
    cerr << "DEBUG: ";
    debug(root);
    cerr << "\n";
    
    if(bf > 1){  // left  too long (implies: has left  child)
        if(val < root->left->val){ // expanded left subtree
            cerr << "left too long; edge\n";
            return right(root);
        }
        if(val > root->left->val){
            cerr << "left too long; middle\n";
            root->left = left(root->left);
            return right(root);
        }
    }
    if (bf < -1){ // right too long (implies: has right child)
        if(val > root->right->val){ // expanded left subtree
            cerr << "right too long; edge\n";
            return left(root);
        }
        if(val < root->right->val){
            cerr << "right too long; middle\n";
            root->right = right(root->right);
            return left(root);
        }
    }
    
    if(root->val == 3) { cerr << "DEBUG: "; debug(root); cerr << "\n"; }
    return root;
}

void inorder(node* n){
    if(n != NULL){
        inorder(n->left);
        cerr << n->val << "(BF="<<balance(n)<<") "; 
        inorder(n->right);
    }
}

void tree(node* n){
    if(n != NULL){
        cerr << n->val << "(BF="<<balance(n)<<") "; 
        tree(n->left);
        tree(n->right);
    }
}

/*int main (){

    ios_base::sync_with_stdio(0);
    int n, a;
    node* root = NULL;
    cin >> n;
    while(n--){
        cin >> a;
        insert(root, a);
    }



    return 0;
}*/