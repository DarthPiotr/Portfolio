#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

#define TAB 20
#define MAX 50
#define TESTS 1

using namespace std;

int n;
ofstream result;
struct iv{
public:
    int begin, end;
} list[TAB];

int rrand(int min, int max){
    return min + rand()%(max-min+1);
}

void solve(){
    int cnt = 0;
    for(int i = -MAX; i <= MAX; i++){
        for(int j = 0; j < n; j++){
            if(i >= list[j].begin && i <= list[j].end){
                cnt++;
                break;
            }
        }
    }

    result << cnt << "\n";
}

int main (){

    ios_base::sync_with_stdio(0);
    srand(time(NULL));
    result.open("rangeres.txt");

    cout << TESTS << "\n";

    for(int xd = 0; xd < TESTS; xd++){
        n = 20;//= rrand(1, TAB);
        cout << n << "\n";
        for(int i = 0; i < n; i++){
            list[i].begin = rrand(-MAX, MAX);
            list[i].end = rrand(list[i].begin, MAX);

            cout << list[i].begin << " " << list[i].end << "\n";
        }
        solve();
    }
    result.close();

    return 0;
}