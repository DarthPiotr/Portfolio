#ifndef _FUNKCJE_
#define _FUNKCJE_

void dodaj(int* a){
    *a += 10;
}

int* zrob_tablice(int rozmiar){
    int* tab = malloc( rozmiar * sizeof(int) );
    printf("w funkcji: %d \n", tab);
    return tab;
}
#endif