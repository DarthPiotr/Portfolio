/*
    TODO:
 _  czytać z pliku liczby zapisane w postaci macierzy.
    Każda kolumna (poza pierwszą) zawiera wynik pomiaru jednego
    z parametrów doświadczenia (zmieniającego się w czasie)
 Dla każdej kolumny program ma wyznaczyć wartości statystyk:
 V suma
 V średnia
 V wariancja
 V odchylenie standardowe
 V max
 V min
 V mediana
 _  Dodatkowo program powinien liczyć korelację pomiędzy poszczególnymi
    parametrami - np przy użyciu współczynników korelacji Pearsona
    (proszę w tym celu użyć zewnętrznej biblioteki gnu scientific library).
    Korelacja ta powinna być przedstawiona w postaci macierzy n_parametrów x n_parametrów.
Warunki dodatkowe:
V tablice w programie mają być zadeklarowane w sposób dynamiczny (malloc)
V każda z liczonych funkcji statystycznych musi być zapisana w osobnej funkcji 
  (wszystkie funkcje z wyjątkiem współczynników korelacji Pearsona implementujemy samodzielnie)
V kod musi być napisany estetycznie i czytelnie- poproszę o dużo komentarzy!
*/
/*
    Program na Podstawy Programowania I
    Kompilowane w standardzie ANSI C90
    >>> gcc -ansi -O3 main.c -o main.exe
    Użycie:
    >>> main.exe < parameters_apo.dat.txt
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_statistics_double.h>
/* maksymalna liczba wierszy - 1068*/
#define ROW 1068
/* maksymalna liczba kolumn - 6*/
#define COL 6
/*
    Sumuje wszystkie elementy kolumny
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy sumę
    Zwraca sumę elementów danej kolumny (col) w macierzy (arr)
*/
double sum_column(double** arr, int r, int col) {
    int i = 0;              /* iterujemy od pierwszego elementu */
    double sum = 0;         /* początkowa suma jest równa 0 */
    while (i < r) {            /* dopóki indeks jest mniejszy od liczby wierszy */
        /*printf("%lf ", arr[i][col]);*/
        sum += arr[i++][col]; /* dodajemy element do sumy oraz zwiększamy indeks o 1 po wykonaniu tej operacji */
    }
    printf("\n");
    return sum;             /* zwróć obliczoną sumę */
}
/*
    Oblicza średnią wszystkich elementów kolumny.
    Używamy algorytmu obliczania średniej kroczącej,
    aby uniknąć przepełnienia zmiennych, które może
    wystąpić w naiwnym algorytmie.
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy średnią
    Zwraca średnią elementów danej kolumny (col) w macierzy (arr)
*/
double average_column(double** arr, int r, int col) {
    int i = 0;                              /* iterujemy od pierwszego elementu; pamiętamy że w danym momencie liczba elementów to i+1 */
    double avg = 0;                         /* początkowa średnia jest równa 0 */
    while (i < r) {                           /* dopóki indeks jest mniejszy od liczby wierszy */
        avg += (arr[i][col] - avg) / (i + 1);   /* dodajemy element do średniej */
        ++i;                                /* zwiększamy indeks o 1 */
    }
    return avg;                             /* zwróć obliczoną średnią */
}
/*
    Oblicza wariancję dla wszystkich elementy kolumny.
    Wykorzystujemy fakt że wariancja to średnia kwadratów
    różnic elementu i średniej, używamy podobnego algorytmu co do średniejs
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy wariancję
    Zwraca owariancję elementów danej kolumny (col) w macierzy (arr)
*/
double variance_column(double** arr, int r, int col) {
    double variance = 0,                    /* początkowa wariancja jest równa 0;*/
        avg = average_column(arr, r, col),   /* obliczamy średnią */
        diff;                            /* zmienna do przechowywania różnicy elementu i średniej */
    int i = 0;                              /* iterujemy od pierwszego elementu; pamiętamy że w danym momencie liczba elementów to i+1 */
    while (i < r) {                           /* dopóki indeks jest mniejszy od liczby wierszy */
        diff = arr[i][col] - avg;           /* obliczamy rożnicę średniej oraz i-tego elementu */
        variance += (diff * diff - variance) / (++i);   /* dodajemy kwadrat różnicy elementu i średniej - do średniej; zwiększamy indeks o 1 */
    }
    return variance;    /* zwróć obliczoną wariancję */
}
/*
    Oblicza odchylenie standardowe dla wszystkich elementy kolumny.
    Odchylenie standardowe to pierwiastek kwaratowy z wariancji.
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy odchylenie standardowe
    Zwraca odchylenie standardowe elementów danej kolumny (col) w macierzy (arr)
*/
double standard_deviation_column(double** arr, int r, int col) {
    return sqrt(variance_column(arr, r, col)); /* zwracamy pierwiastek kwadratowy z wariancji */
}
/*
    Znajduje maksymalny element kolumny.
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy maksimum
    Zwraca maksymalny element danej kolumny (col) w macierzy (arr)
*/
double max_column(double** arr, int r, int col) {
    double max = arr[0][col];   /* za największy element przyjmujemy pierwszy element kolumny */
    int i = 1;                  /* przeszukiwanie zaczynamy od kolejnego elementu */
    while (i < r) {              /* dopóki indeks jest mniejszy od liczby wierszy */
        if (arr[i][col] > max)   /* jeśli i-ty element jest większy niż obecnie zapamiętane maksimum */
            max = arr[i][col];  /* to ten element jest nowym maksimum */
        ++i;                    /* zwiększamy indeks o 1 */
    }
    return max;                 /* zwracamy maksimum */
}
/*
    Znajduje minimalny element kolumny.
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy minimum
    Zwraca minimalny element danej kolumny (col) w macierzy (arr)
*/
double min_column(double** arr, int r, int col) {
    double min = arr[0][col];   /* za najmniejszy element przyjmujemy pierwszy element kolumny */
    int i = 1;                  /* przeszukiwanie zaczynamy od kolejnego elementu */
    while (i < r) {              /* dopóki indeks jest mniejszy od liczby wierszy */
        if (arr[i][col] < min)   /* jeśli i-ty element jest mniejszy niż obecnie zapamiętane minimum */
            min = arr[i][col];  /* to ten element jest nowym minimum */
        ++i;                    /* zwiększamy indeks o 1 */
    }
    return min;                 /* zwracamy minimum */
}
/*
    Sortowanie szybkie (quicksort)
    arr - tablica do posortowania
    beg - indeks pierwszego elementu tablicy do posortowania
    end - indeks ostatniego elementu tablicy do posortowania
*/
void quicksort(double* arr, int beg, int end) {
    int l = beg, r = end;               /* zapamiętujemy indeksy do elementu najbardziej na lewo oraz na prawo */
    double pivot = arr[(l + r) / 2],    /* wyznaczamy element podziałowy (pivot), względem któego będziemy porównywać wartości */
        t;                          /* przygotowujemy zmienną pomocniczą*/
    do {                            /* rozpoczynamy pętlę porównującą elemety do pivotu */
        while (arr[l] < pivot)      /* dopóki lewy indeks zawiera liczbę mniejszą od pivotu (liczba jest "po dobrej stronie") */
            ++l;                    /* to przesuwamy lewy indeks na kolejny od lewej element */
        while (pivot < arr[r])      /* dopóki prawy indeks zawiera liczbę większą od pivotu (liczba jest "po dobrej stronie") */
            --r;                    /* to przesuwamy prawy indeks na kolejny od prawej element */
        /* powyższe pętle doprowadziły do sytuacji w której lewy i prawy indeks wskazują na elementy które są "po złej stronie",
           więc można je zamienić ze sobą miejscami, aby znalazły się " po dobrej stronie"
           albo element wskazywany przez lewy indeks jest po prawej stronie elementu wskazywanego przez prawy indeks,
           wtedy niczego nie zamieniamy, a kończymy pętlę*/
        if (l <= r) {               /* jeśli jest to sytuacja w której możemy zamienić, to zamieniamy elementy miejscami */
            t = arr[l];             /* w zmiennej pomocniczej zapamiętujemy wartość lewego elementu */
            arr[l] = arr[r];        /* do lewego elemetu przepisujemy wartość prawego elementu */
            arr[r] = t;             /* do prawego element przepisujemy zapamiętaną wartość lewego elementu */
            ++l; --r;               /* przesuwamy obydwa indeksy na koleje - odpowiednio od prawej i od lewej - elementy */
        }
    } while (l <= r);               /* jeśli jest to sytuacja w której indeksy są w odpowiedniej kolejności, wykonujemy pętlę ponownie */
    if (l < end) quicksort(arr, l, end); /* Jeśli lewy indeks nie jest na końcu tablicy, to należy posortować pozostałą prawą część tablicy */
    if (beg < r) quicksort(arr, beg, r); /* Jeśli prawy indeks nie jest na początku tablicy, to należy posortować pozostałą lewą część tablicy */
}
/*
    Znajduje medianę elementów kolumny.
    Używany jest algporytm, który znajduje medianę w posortowanym zbiorze,
    ze względu na to, że chcemy zwrócić medianę, a bardziej zaawansowane
    algorytmy zwracają medianę górną w przypadku parzystych liczebności zbioru,
    zamiast średniej dwóch środkowych elementów.
    arr - macierz z danymi
    r   - liczba wszystkich wierszy
    col - indeks kolumny dla której zwracamy medianę
    Zwraca medianę elementów danej kolumny (col) w macierzy (arr)
*/
double median_column(double** arr, int r, int col) {
    /* tworzymy tablicę tymczasową, w której będziemy przechowywać wszystkie
       dane z kolumny, aby przekazać je do funkcji sorującej */
    double* array = (double*)malloc(sizeof(double) * r);
    double result = 0;          /* przygotowujemy zmienną do zapisania wyniku, po wyczyszczeniu pamięci */
    int i = 0;                  /* przepisujemy tablicę, zaczynając od pierwszego elementu */
    while (i < r) {             /* dopóki indeks jest mniejszy od liczby wierszy */
        array[i] = arr[i][col]; /* przepisujemy i-ty element z macierzy do tablicy*/
        ++i;                    /* przechdzimy do kolejnego indeksu */
    }
 /* wyszukujemy medianę dla zakresu od pierwszego do ostatniego elementu;
    wynik zapisujemy do zmiennej, aby zwrócić go po zwolnieniu pamięci */
    quicksort(array, 0, r - 1);
    if (r % 2 == 1)                                      /* dla nieparzystej liczności zbioru*/
        result = array[r / 2];                          /* mediana jest środkowym elementem */
    else                                                /* dla parzystej liczności zbioru*/
        result = (array[r / 2] + array[r / 2 - 1]) / 2; /* mediana jest środkowym elementem */
    free(array);    /* zwalniamy miejsce w pamięci */
    return result;  /* zwracamy medianę */
}
/*
    Punkt wejściowy programu
*/
int main(void) {
    int i, j; /* deklaracja zmiennych potrzebnych do pętli */
    double** arr = (double**)malloc(sizeof(double*) * ROW); /* tworzenie macierzy do przechowywania danych */
    double a1[] = {0, 34.5, 123.21, 11.1};
    double a2[] = {0, 68.123, 250.1, 22.5};
    double res = -123;
    
    /* bardzo brzydkie, tymczasowe wczytywanie ze standardowego wejścia */
    i = 0;
    while (i < ROW) {
        arr[i] = (double*)malloc(sizeof(double) * COL);
        j = 0;
        while (j < COL) {
            scanf("%lf", &(arr[i][j]));
            ++j;
        }
        ++i;
    }
    i = 1;              /* zaczynając od drugiej kolumny (bo pierwsza zawiera jedynie liczbę porządkową) */
    while (i < COL) {   /* przechodziwmy przez wszystkie kolumny i liczymy wartości funkcji statystycznych */
        printf("Kolumna %d :\n", i);
        printf("Suma: %lf\n",               sum_column               (arr, ROW, i)); /* oblliczenie sumy      */
        printf("Srednia: %lf\n",            average_column           (arr, ROW, i)); /* oblliczenie średniej  */
        printf("Wariancja: %lf\n",          variance_column          (arr, ROW, i)); /* oblliczenie wariancji */
        printf("Odch. standardowe: %lf\n",  standard_deviation_column(arr, ROW, i)); /* oblliczenie odchylenia standardowego */
        printf("Max: %lf\n",                max_column               (arr, ROW, i)); /* oblliczenie maksimum  */
        printf("Min: %lf\n\n",              min_column               (arr, ROW, i)); /* oblliczenie minimum   */
        printf("Mediana: %lf\n\n",          median_column            (arr, ROW, i)); /* oblliczenie mediany   */
        ++i;
    }
    res = gsl_stats_correlation(a1, 1.0f, a2, 1.0f, 4);
    printf("Pearsona: %lf\n", res);
    /* zwalnianie pamięci macierzy */
    i = 0;                          /* od pierwszej kolumny */
    while (i < COL) free(arr[i++]); /* do ostatniej kolumny, zwalniamy pamięć */
    free(arr);                      /* zwalniamy pamięć dla wierszy */
    return 0;
}