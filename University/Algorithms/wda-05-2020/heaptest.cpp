#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

int Q;
int len, lencopy;
int tab[1000];
int tabcopy[1000];

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
    int child = 1+ index*2;

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

int min(){
    int m = tab[0];
    for(short i = 1; i < len; i++)
        if(tab[i] < m)
            m = tab[i];
    return m;
}

int rrand(int min, int max){
    return min + rand()%(max-min+1);
}

bool checkTree(int vert = 0){
    int child1 = 1+ vert*2;
    int child2 = child1+1;

    if(vert >= len)
        return true;

    if (child1 < len)
        if(tab[child1] < tab[vert])
        return false;

    if(child2 < len)
        if(tab[child2] < tab[vert])
            return false;

    return checkTree(child1) && checkTree(child2);
}

void execute(int type, int arg){
    switch (type)
        {
        case 1:     //   ADD
            tab[len++] = arg;
            heapParent(len-1);
            break;
        case 2:     // DELETE
            swap(tab[arg], tab[--len]);
            heapChildren(arg);
            heapParent(arg);
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

int main (){

    int n, v;
    srand(time(NULL));
    ios_base::sync_with_stdio(0);

    Q = 100000;
    len = 0;
    bool paramok;
    bool noerror = true;

    //for (int i = 0; i < Q; i++)
    while(noerror)
    {
        
        if      (len <= 0 /*|| i < 10*/) n = 1;
        else if (len >= 1000)        n = 2; 
        else                         n = rrand(1,2);

        lencopy = len;
        copy(begin(tab), end(tab), begin(tabcopy));

        switch(n){
            case 1:
                paramok = false;
                while(!paramok){
                    v = rrand(1, 10000);
                    paramok = search(v,0) == -1;
                }
                execute(1, v);
                break;
            case 2:
                v = rrand(0, len-1);
                execute(2, v);
        }

        /*cout << (n == 1 ? "ADD " : "REM ") << v << "\n";
        for(int j = 0; j < len; j++)
                    cout << tab[j] << ", ";
        cout << "\n\n";*/

        if(len > 0)
            if(!checkTree()){
                noerror = false;
                cout << "!! ---\nTREE CONSISTENCY lost on operation "<< (n == 1 ? "ADD " : "REM i:") << v <<" \nBefore:\n";
                for(int j = 0; j < lencopy; j++)
                    cout << tabcopy[j] << ", ";
                cout << "\nAfter:\n";
                for(int j = 0; j < len; j++)
                    cout << tab[j] << ", ";
                cout << "\n  ---\n";
            }
            else if(tab[0] != min())
                //cout << "TEST OK\n";
            //else
            {
                noerror = false;
                cout << "!! ---\nERROR occured on operation "<< (n == 1 ? "ADD " : "REM i:") << v <<" \nBefore:\n";
                for(int j = 0; j < lencopy; j++)
                    cout << tabcopy[j] << ", ";
                cout << "\nAfter:\n";
                for(int j = 0; j < len; j++)
                    cout << tab[j] << ", ";
                cout << "\n  ---\n";
            }
        //else i--;
    }

    return 0;
}