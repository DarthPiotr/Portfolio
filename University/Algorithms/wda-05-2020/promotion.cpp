#include <iostream>
#include <cmath>

#define SIZE 1000000

using namespace std;

int n;
// max 1 dnia = 10^5 
// max 2 dnia = 10^5 -2 + 10^5
// max 3 dnia = 10^5 -2 + 10^5 -2 + 10^5
// max n-tego dnia = 10^5 + (n-1)(10^5 -2)
// max 5000 dnia = 10^5 + 4999(10^5-2) = 499990002
int tab[SIZE]; // min-max heap
int len;

// Pomoce naukowe:
// https://en.wikipedia.org/wiki/Min-max_heap
// https://github.com/itsjohncs/minmaxheap-cpp/blob/master/MinMaxHeap.hpp

bool minlevel(int index){
   return (int)log2(index+1) % 2 == 0;
}

void heapParentMin(int index){
    if (index <= 2)
        return;

    //int parent = (((index-1)/2)-1)/2
    int parent = (index-3)/4;

    if(tab[index] < tab[parent]){
        swap(tab[index], tab[parent]);
        heapParentMin(parent);
    }
}

void heapParentMax(int index){
    if (index <= 2)
        return;

    //int parent = (((index-1)/2)-1)/2
    int parent = (index-3)/4;

    if(tab[index] > tab[parent]){
        swap(tab[index], tab[parent]);
        heapParentMax(parent);
    }
}

void heapParent(int index){
    if(index == 0)
        return;

    int parent = (index-1)/2;
    if(minlevel(index)){
        if(tab[index] > tab[parent]){
            swap(tab[index], tab[parent]);
            heapParentMax(parent);
        }
        else
            heapParentMin(index);
    }
    else
    {
        if(tab[index] < tab[parent]){
            swap(tab[index], tab[parent]);
            heapParentMin(parent);
        }
        else
            heapParentMax(index);
    }
}

void heapChildMin(int index){
    int child = 2*index + 1;
    //int gchild = 2*(2*index+1)+1;
    int gchild = 4*index + 3;

    if(child >= len)
        return;

    // znajdz najmniejsze dziecko    
    if(child+1 < len && tab[child+1] < tab[child])
        child = child+1;

    bool smallestgchild = false;
    // znajdz najmniejszego wnuka
    for(short i = 0; i < 4 && gchild+i < len; i++){
        if(tab[gchild+i] < tab[child]){
            child = gchild+i;
            smallestgchild = true;
        }
    }

    if(smallestgchild){
        if(tab[child] < tab[index]){
            swap(tab[child], tab[index]);
            int smallestparent = (child-1)/2;
            if(tab[child] > tab[smallestparent]){
                swap(tab[child], tab[smallestparent]);
            }
            heapChildMin(child);
        }   
    }
    else if (tab[child] < tab[index]){
        swap(tab[child], tab[index]);
    }
}

void heapChildMax(int index){
    int child = 2*index + 1;
    //int gchild = 2*(2*index+1)+1;
    int gchild = 4*index + 3;

    if(child >= len)
        return;

    // znajdz najmniejsze dziecko    
    if(child+1 < len && tab[child+1] > tab[child])
        child = child+1;

    bool smallestgchild = false;
    // znajdz najmniejszego wnuka
    for(short i = 0; i < 4 && gchild+i < len; i++){
        if(tab[gchild+i] > tab[child]){
            child = gchild+i;
            smallestgchild = true;
        }
    }

    if(smallestgchild){
        if(tab[child] > tab[index]){
            swap(tab[child], tab[index]);
            int smallestparent = (child-1)/2;
            if(tab[child] < tab[smallestparent]){
                swap(tab[child], tab[smallestparent]);
            }
            heapChildMax(child);
        }   
    }
    else if (tab[child] > tab[index]){
        swap(tab[child], tab[index]);
    }
}

void heapChild(int index){
    if(minlevel(index))
        heapChildMin(index);
    else
        heapChildMax(index); 
}

void add(int value){
    tab[len++] = value;
    heapParent(len-1);
}

void remove(int index){
    swap(tab[index], tab[--len]);
    heapChild(index);
}

void show(){
    int max, min;
    max = min = tab[0];
    for(int i = 0; i < len; i++){
        cout << tab[i] << ", ";
        if(tab[i] > max) max = tab[i];
        if(tab[i] < min) min = tab[i];
    }
    cout << "\nMAX: " << max << ", MIN: " << min << "\n";
}

int main (){

    ios_base::sync_with_stdio(0);

    int j, k, tmp;
    int max, min;
    long long sum = 0;

    cin >> n;
    len = 0;
    for(int i = 0; i < n; i++){
        cin >> k;
        //cout << "Adding...\n";
        // wczytaj i dodaj
        for(j = 0; j < k; j++){
            cin >> tmp;
            add(tmp);
            //show();
            //cout << "\n";
        }

        //cout  << "\nBefore:\n";
        //show();        

        // usun i policz
        min = tab[0];
        max = tab[1];
        if(len >= 3){
            if(tab[2] > max){
                max = tab[2];
                remove(2);
            }
            else
                remove(1);
        }

        //cout << "After rem MAX:\n";
        //show(); 

        remove(0);
        //cout << "After rem MIN:\n";
        //show();
        //cout << "\n"; 
        
        sum += max-min; 
    }

    cout << sum;

    return 0;
}