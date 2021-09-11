#include <iostream>

void funkcja_jeden(int* a){ // jawnie prosimy o wskaźnik jako argument
    *a += 10; // wykonujemy operację na wskaźniku do orginalnej zmiennej
}

void funkcja_dwa(int& a){ // prosimy o zmienną i niejawnie bierzemy do niej wskaźnik
    a += 20; // tu też wykonujemy operację na wskaźniku do orginalnej zmiennej,
             // ale nie musimy się męczyć ze składnią wskaźników
}

int main(){

    int x = 5;  // x = 5

    funkcja_jeden(&x); // przekazujemy wskaźnik do x i sami musimy o to zadbać
    // x = 15;

    funkcja_dwa(x); // przekazujemy x i funkcja już wie że ma wziąć wskaźnik
    // x = 35;

    std::cout << x;
}