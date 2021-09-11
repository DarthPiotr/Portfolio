#include <iostream>
#include <algorithm>

#define HEAPSIZE (int)1e6

using namespace std;

int z, n;

struct iv{
public:
    int begin, end;
};

iv heap[HEAPSIZE];
int last;

inline bool isGreater(iv i1, iv i2){
    return i1.begin > i2.begin;
}

void heapParent(int index) {
    if(index == 0)
        return;
    
    int parent = (index-1)/2;

    if(isGreater(heap[parent], heap[index])){
        swap(heap[parent], heap[index]);
        heapParent(parent);
    }
}

void heapChildren(int index) {
    int child = 1 + index*2;

    if(child >= last)
        return;

    if(child+1 < last)
        if (isGreater(heap[child], heap[child+1]))
            child = child+1;
    
    if(isGreater(heap[index], heap[child])){
        swap(heap[index], heap[child]);
        heapChildren(child);
    }
}

int main (){

    ios_base::sync_with_stdio(0);
    int i, j;//,
    //ix; // soritng?
    int number;
    iv current, prev;

    cin >> z;
    for(j = 0; j < z; j++){
        cin >> n;

        last = 0;
        for(i = 0; i < n; i++){
            cin >> heap[last].begin >> heap[last].end;
            heapParent(last++);
            //last++; // sorting?
        }

        /*sort(
             heap,
             heap+last,
             [](const iv &a, const iv &b) -> bool { return a.begin < b.begin; }
        ); // sorting?
        */

        //ix = 0; // sorting?
        prev = heap[0/*ix*/];
        number = prev.end - prev.begin + 1;
        while(last > 0/*ix < last*/){
            current = heap[0/*ix++*/];
            swap(heap[0], heap[--last]);
            heapChildren(0);

            if(current.end > prev.end){
                if(current.begin <= prev.end){
                    number += current.end - prev.end;
                    prev.end = current.end;
                }
                else{
                    number += current.end - current.begin + 1;
                    prev.begin = current.begin;
                    prev.end = current.end;
                }
            }
        }

        cout << number << "\n";
    }


    return 0;
}