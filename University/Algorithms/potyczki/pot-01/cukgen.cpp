#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

int rrand(int min, int max){
    return min + rand()%(max-min+1);
}

int main (){

    srand(time(NULL));

    ios_base::sync_with_stdio(0);

    int sum = 0, num = 1;
    cout << 5000 << "\n";
    for(int i = 0; i < 5000; i++)
    {
        num = rrand(min(num, 5000), min(sum+1, 5000));
        sum += num;
        cout << num << " ";
    }

    return 0;
}