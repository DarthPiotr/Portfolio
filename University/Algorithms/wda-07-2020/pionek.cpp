#include <iostream>
#include <string>

#define DICEMAX 6

using namespace std;

struct field{
public:
    short value = 0;
    long long max = 0;
} tab[1000000];
int n;

int main (){

    ios_base::sync_with_stdio(0);

    int i, j;
    long long max;

    cin >> n;
    for(i=0; i < n; i++){
        cin >> tab[i].value;
        max = i == 0 ? 0 : INT64_MIN;
        for(j = i-1; j >= i-DICEMAX && j >= 0; j--){
            if(max < tab[j].max)
                max = tab[j].max;
        }
        tab[i].max = max + (long long)tab[i].value;
    }

    cout << tab[n-1].max;
    
    return 0;
}