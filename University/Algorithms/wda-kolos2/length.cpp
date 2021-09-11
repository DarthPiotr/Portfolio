#include <iostream>
#include <cmath>

int main (){
    int a;
    while(std::cin >> a)
        std::cout << (a <= 0 ? 1 : (int)(log2f(a)+1)) << "\n";
    return 0;
}