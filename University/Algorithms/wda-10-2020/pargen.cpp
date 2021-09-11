#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

short tab[1000000];
int len;

int rrand(int min, int max){
    return min + rand()%(max-min+1);
}

int index(int i, int k, int n){
    return (i+k)%n;
}

int main () {

    ios_base::sync_with_stdio(0);
    srand(time(NULL));

    ofstream test("paroatest.txt");
    ofstream resu("parresu.txt");

    int i, k;
    int sum, res;
    int n = rrand(1, 10);

    test << n << "\n";

    for(i = 0; i < n; i++){
        tab[len] = rrand(-8, 10);
        test << tab[len++] << " ";
    }
    test << "\n0\n\n";
    
    res = n;
    bool bad;
    for(k = 0; k < n; k++){
        sum = 0;
        bad = false;
        for(i = 0; i < n; i++){
            sum += tab[index(i,k,n)];
            if(sum < 0){
                res--;
                bad = true;
                break;
            }
            
        }
        if(!bad){
            test << "k: " << k << "; ";
            for(i = 0; i < n; i++){
                test << tab[index(i,k,n)] << " ";
            }
            test << "\n";
        }
    }

    resu << res << "\n";

    test.close();
    resu.close();


    return 0;
}