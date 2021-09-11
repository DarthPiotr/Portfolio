#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

const int TEST = 20;
const int NUMS = 200000;
const long long MAXNUM = 10000000;

int random(int min, int max){
    return min + rand() % (max-min+1);
}

long long random(long long min, long long max){
    return min + rand() % (max-min+1);
}

long long *tab;

long long solve(int l){
    long long cnt = 0;
    for(int i = 0; i < l; i++){
        for(int j = i+1; j < l; j++){
            if(tab[j] < tab[i])
                cnt++;
        }
    }
    return cnt;
}

int main(){

    ios_base::sync_with_stdio(0);
    srand(time(NULL));

    ofstream test, result;
    test.open("test.txt");
    result.open("result.txt");

    test << TEST << "\n\n"; 
    for(int i = 0; i < TEST; i++){
        int curr = random(1, NUMS);
        test << curr << "\n";
        tab = new long long[curr];
        for(int j = 0; j < curr; j++){
            long long r = random((long long)1, MAXNUM);
            test << r << "\n";
            tab[j] = r;
        }
        result << solve(curr) << "\n";
        test << "\n";
    }

    test.close();
    result.close();

    return 0;
}