#include <stdio.h>
#include <string.h>

struct komp{
    int numer;
    char nazwa[10];
};

int main (){

    struct komp * tablica [100] = {0};
    memset(tablica, 0, sizeof(tablica));

    printf("%d", tablica[99] == NULL);

    return 0;
}