#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct elem{
    elem(){}
    elem(int v, int w) : value(v), weight(w) {}
    int value, weight;
} tab[5];

int main (){

    ios_base::sync_with_stdio(0);
    tab[0] = elem(9, 2);
    tab[1] = elem(4, 1);
    tab[2] = elem(15, 5);
    tab[3] = elem(8, 3);
    tab[4] = elem(8, 3);

    int dp[5][10] = {0};

    for(int i = 0, j; i < 5; i++){
        for(j = 0; j < 10; j++){
            if(j - tab[i].weight >= 0) { // can add
                dp[i][j] = max(
                                (i-1 >= 0 ? dp [i-1] [j] : 0),
                                (i-1 >= 0 ? dp [i-1] [j - tab[i].weight] : 0)  + tab[i].value 
                            );
            } else{ // dont add
                dp[i][j] = i-1 >= 0 ? dp[i-1][j] : 0;
            }

            cout << setw(3) << dp[i][j];
        }
        cout << "\n";
    }

    return 0;
}