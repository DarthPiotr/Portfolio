#include <iostream>

using namespace std;

int tab[3][3] {{1, 2, 3},
               {4, 5, 6},
               {7, 8, 9}};

int main (){
    ios_base::sync_with_stdio(0);
    int i, j, k, l, m ,n;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            
            for(k = i; k < 3; k++){
                for(l = j; l < 3; l++){
                    int sum = 0;
                    for(m = i; m <= k; m++){
                        for(n = j; n <= l; n++){
                            sum += tab[m][n];
                        }
                    }
                    cout << sum << "\n";
                }
            }

        }
    }


    return 0;
}