#include <iostream>

using namespace std;

int Q;
int *tab;
int len;

void heapParent(int index) {
    if(index == 0)
        return;
    
    int parent = (index-1)/2;

    if(tab[parent] > tab[index]){
        swap(tab[parent], tab[index]);
        heapParent(parent);
    }
}

void heapChildren(int index) {
    int child = 1 + index*2;

    if(child >= len)
        return;

    if(child+1 < len)
        if (tab[child+1] < tab[child])
            child = child+1;
    
    if(tab[index] > tab[child]){
        swap(tab[index], tab[child]);
        heapChildren(child);
    }
}

// zwraca indeks elementu
int search(int value, int index){
    if(index >= len)
        return -1;

    if(tab[index] == value)
        return index;


    int result = -1,
        c1 = index*2+1,
        c2 = index*2+2;
    
    if(c1 < len)
        if(tab[c1] <= value)
            result = search(value, c1);
    if(result == -1 && c2 < len)
        if(tab[c2] <= value)
            result = search(value, c2);

    return result;
}

void addHeap(int v){
    tab[len++] = v;
    heapParent(len-1);
}

int popMax(){
    swap(tab[0], tab[--len]);
    heapChildren(0);
}

int main (){

    int n, v;
    ios_base::sync_with_stdio(0);

    cin >> Q;
    tab = new int[Q];
    len = 0;

    for (int i = 0; i < Q; i++){
        cin >> n;
        switch (n)
        {
        case 1:     //   ADD
            cin >> v;
            addHeap(v);
            break;
        case 2:     // DELETE
            cin >> v;
            //val = v;
            v = search(v, 0);
            swap(tab[v], tab[--len]);
            heapChildren(v);
            heapParent(v);
            break;
        case 3:     // PRINT MIN
            if (len > 0)
                cout << tab[0];
            cout << "\n";
            break;
        default:
            break;
        }
    }

    return 0;
}