#include <iostream>

using namespace std;

short t, n;
int tab[100000];

// Quicksort na podstawie wersji z wykladu
// sortuje malejaco bo dla wiekszosci* przypadkow
// n^(n+k) > (n+k)^n
// * wyjatkiem jest 3^2 > 2^3
// dla ustalonych, naturalnych n > 1, k >= 1
void quickSort(int start, int end){
    int left = start;
    int right = end;
    int mid = tab[(right+left)/2];

    do{
        while(mid < tab[left]){
            left++;
        }
        while(tab[right] < mid){
            right--;
        }
        if(left <= right){
            swap(tab[left++], tab[right--]);
        }
    } while(left <= right);

    if(left < end) quickSort(left, end);
    if(right > start) quickSort(start, right);
}

int main(){

    int i, j;

    ios_base::sync_with_stdio(0);
    
    cin >> t;
    for(i = 0; i < t; i++){
        cin >> n;
        for(j = 0; j < n; j++){
            cin >> tab[j];
        }

        quickSort(0, n-1);

        // Najlepiej zeby od razu pozbyc sie 1
        for(j = n-1; j >= 0 && tab[j] == 1; j--){
            cout << "1 ";
            n--;
        }

        // 3^2 > 2^3
        if(n == 2 && tab[0] == 3 && tab[1] == 2){
            cout << "2 3 \n";
            continue;
        }

        // wypisz reszte
        for(j = 0; j < n; j++){
            cout << tab[j] << " ";
        }
        cout << "\n";
    }

    return 0;
}