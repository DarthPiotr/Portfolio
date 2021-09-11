#include <iostream>

using namespace std;

int main (){
    int tab[15] = {1, 5, 34, 12, 75, 9, 324, 8732, 10, 51, 44, 85, 100, 23, 190};
    int sum = 0, num = 0, min = 50;

    cout << "Liczby podzielne przez 5:\n";
    for(int i = 0; i < 15; i++){
        if(tab[i] % 5 == 0)
            cout << tab[i] << " ";
        if(tab[i] < 50){
            sum += tab[i];
            num++;
            if(tab[i] < min)
                min = tab[i];
        }
    }

    if(num > 0){
        cout << "\nLiczby mniejsze of 50:\n";
        cout << "Suma:    " << sum << "\n";
        cout << "Minimum: " << min << "\n";
        cout << "Srednia: " << (double)sum/num << "\n";
    }
    else
        cout << "Nie ma liczb mniejszych od 50\n";
    
    return 0;
}