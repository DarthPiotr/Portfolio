#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main (){
    srand(time(NULL));

    int num, np=0, max = 1001, min = 0, licz = 0;
    cout << "Liczby nieparzyste:\n";
    for(int i = 0; i < 10; i++){
        num = 1 + rand()%1000;
        if(num % 2){
            cout << num << " ";
            licz++;
        }

        if(num > max) max = num;
        if(num < min) min = num;

        if(num % 7 == 0) break;
    }
    cout << "\nMaksimum: " << max << "\n";
    cout <<   "Minimum:  " << min << "\n";


    return 0;
}