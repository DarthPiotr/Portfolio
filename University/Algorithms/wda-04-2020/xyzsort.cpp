#include <iostream>
#include <string>

using namespace std;

short t;

struct point {
public:
    short x, y, z;
} *tab;

bool isGreater(const point &a, const point &b){
    if(a.x != b.x) return a.x > b.x;
    if(a.y != b.y) return a.y > b.y;
    return a.z > b.z;
}

// Quicksort na podstawie wersji z wykladu
void quickSort(short start, short end){
    short left = start;
    short right = end;
    point mid = tab[(right+left)/2];

    do{
        while(isGreater(mid, tab[left])){
            left++;
        }
        while(isGreater(tab[right], mid)){
            right--;
        }
        if(left <= right){
            swap(tab[left++], tab[right--]);
        }
    } while(left <= right);

    if(left < end) quickSort(left, end);
    if(right > start) quickSort(start, right);
}

int main() {
    short i;

    ios_base::sync_with_stdio(0);

    cin >> t;

    tab = new point[t];

    for(i = 0; i < t; i++){
        cin >> tab[i].x >> tab[i].y >> tab[i].z;
    }

    quickSort(0, t-1);

    for(i = 0; i < t; i++){
        cout << tab[i].x << " " << tab[i].y << " " << tab[i].z << "\n";
    }

    delete[] tab;

    return 0;
}