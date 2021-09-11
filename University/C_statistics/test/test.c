#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funkcje.c"
#include "funkcje.c"

#define GRUCHA(a) strcpy(str, (a) );
#define MNOZENIE(a, b) (a) * (b)

struct test
{
    int a;
};

int main(){
    int a = 5;
    int b = 2;

    const int x = 5000;

    printf("%d \n", MNOZENIE(3 + 2, b));
    // printf("%d \n", (3 + 2) * (b));

    char str[100] = "zbysiu walczak";// {'z', 'b', 'y' ...}

#ifdef _DEBUG

    GRUCHA("jacek gruszka")

    printf("%s \n", str);
    
    //scanf("%d \n", &a);
    dodaj(&a);

    printf("%d \n", a);

    int* ptr = zrob_tablice(10);

    printf("w main: %d \n", ptr);
    free(ptr);

#endif

    

    return 0;
}
