#include <iostream>

using namespace std;

int t, n;
long long invcnt;
int tab[200000];
int tmp[200000];

// Merge sort na podstawie wykladu
void mergeSort(int start, int end){
    if(start == end) return;

    int mid = (start+end)/2;

    mergeSort(start, mid);
    mergeSort(mid+1, end);

    int l = start;
    int r = mid+1;
    int res = start;
    int i;

    while(l <= mid && r <= end){
        if(tab[l] <= tab[r]) {
            tmp[res++] = tab[l++];
        }
        else {
            invcnt += mid-l+1;
            tmp[res++] = tab[r++];
        }
    }

    for(i = l; i <= mid; i++){
        tmp[res++] = tab[i];
    }
    for(i = r; i <= end; i++){
        tmp[res++] = tab[i];
    }
    for(i = start; i <= end; i++){
        tab[i] = tmp[i];
    }
}

int main(){

    ios_base::sync_with_stdio(0);

    cin >> t;
    for(int i = 0; i < t; i++){
        cin >> n;
        for(int j = 0; j < n; j++){
            cin >> tab[j];
        }

        invcnt = 0;
        mergeSort(0, n-1);

        cout << invcnt << "\n";
    }

    return 0;
}