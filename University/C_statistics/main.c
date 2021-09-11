/*
    TODO:
 V  czytać z pliku liczby zapisane w postaci macierzy.
    Każda kolumna (poza pierwszą) zawiera wynik pomiaru jednego
    z parametrów doświadczenia (zmieniającego się w czasie)
 Dla każdej kolumny program ma wyznaczyć wartości statystyk:
 V suma
 V średniaf
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
    Kompilowane w standardzie C99
    >>> gcc main.c -std=c99 -pedantic -O3 -Wall -static -lm -lgsl -lgslcblas -o main.exe

    Użycie:
    >>> main.exe [nazwa_pliku_wejściowego]
        nazwa_pliku_wejściowego - (opcjonalnie) plik z którego dane mają zostać wczytane (domyślnie: parameters_apo.dat.txt)
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <gsl/gsl_statistics_double.h>

/*
    --- definicje stałych ---

    COL         -   dokładna liczba kolumn w pliku wejściowym
    ROW         -   maksymalna liczba wierszy w pliku wejściowym.
                    Jeśli w pliku jest więcej wierszy niż określono w ROW, zostaną pominięte.
    FILENAME    -   domyślna nazwa pliku wejściowegos
*/
#define COL 6
#define ROW 5000
#define FILENAME "parameters_apo.dat.txt"

/*
    Sumuje wszystkie elementy kolumny
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca sumę elementów tablicy (arr)
*/
double sum_column(double *arr, int len)
{
    double sum = 0;               /* początkowa suma jest równa 0 */
    for (int i = 0; i < len; ++i) /* iterujemy po wszystkich elementach (wierszach)*/
        sum += arr[i];            /* dodajemy element do sumy oraz zwiększamy indeks o 1 po wykonaniu tej operacji */
    return sum;                   /* zwróć obliczoną sumę */
}

/*
    Oblicza średnią wszystkich elementów kolumny.
    Używamy algorytmu obliczania średniej kroczącej,
    aby uniknąć przepełnienia zmiennych, które może
    wystąpić w naiwnym algorytmie.
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca średnią elementów tablicy (arr)
*/
double average_column(double *arr, int len)
{
    double avg = 0;                      /* początkowa średnia jest równa 0 */
    for (int i = 0; i < len; ++i)        /* iterujemy po wszystkich elementach (wierszach); liczba elementów w danym momencie jest równa i+1*/
        avg += (arr[i] - avg) / (i + 1); /* dodajemy element do średniej */
    return avg;                          /* zwróć obliczoną średnią */
}

/*
    Oblicza wariancję dla wszystkich elementy kolumny.
    Wykorzystujemy fakt że wariancja to średnia kwadratów
    różnic elementu i średniej, używamy podobnego algorytmu co do średniejs
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca wariancję elementów tablicy (arr)
*/
double variance_column(double *arr, int len)
{
    double variance = 0,                /* początkowa wariancja jest równa 0;*/
        avg = average_column(arr, len), /* obliczamy średnią */
        diff;                           /* zmienna do przechowywania różnicy elementu i średniej */
    for (int i = 0; i < len; ++i)
    {                                                   /* iterujemy po wszystkich elementach (wierszach) */
        diff = arr[i] - avg;                            /* obliczamy rożnicę średniej oraz i-tego elementu */
        variance += (diff * diff - variance) / (i + 1); /* dodajemy kwadrat różnicy elementu i średniej - do średniej; zwiększamy indeks o 1 */
    }
    return variance; /* zwróć obliczoną wariancję */
}

/*
    Oblicza odchylenie standardowe dla wszystkich elementy kolumny.
    Odchylenie standardowe to pierwiastek kwaratowy z wariancji.
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca odchylenie standardowe elementów tablicy (arr)
*/
double standard_deviation_column(double *arr, int len)
{
    return sqrt(variance_column(arr, len)); /* zwracamy pierwiastek kwadratowy z wariancji */
}

/*
    Znajduje maksymalny element kolumny.
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca maksymalny element tablicy (arr)
*/
double max_column(double *arr, int len)
{
    double max = arr[0];          /* za największy element przyjmujemy pierwszy element kolumny */
    for (int i = 1; i < len; ++i) /* iterujemy po wszystkich elementach (wierszach); zaczynając od drugiego */
        if (arr[i] > max)         /* jeśli i-ty element jest większy niż obecnie zapamiętane maksimum */
            max = arr[i];         /* to ten element jest nowym maksimum */
    return max;                   /* zwracamy maksimum */
}

/*
    Znajduje minimalny element kolumny.
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca minimalny element tablicy (arr)
*/
double min_column(double *arr, int len)
{
    double min = arr[0];          /* za najmniejszy element przyjmujemy pierwszy element kolumny */
    for (int i = 1; i < len; ++i) /* iterujemy po wszystkich elementach (wierszach); zaczynając od drugiego */
        if (arr[i] < min)         /* jeśli i-ty element jest mniejszy niż obecnie zapamiętane minimum */
            min = arr[i];         /* to ten element jest nowym minimum */
    return min;                   /* zwracamy minimum */
}

/*
    Sortowanie szybkie (quicksort)
    arr - tablica do posortowania
    beg - indeks pierwszego elementu tablicy do posortowania
    end - indeks ostatniego elementu tablicy do posortowania
*/
void quicksort(double *arr, int beg, int end)
{
    int l = beg, r = end;            /* zapamiętujemy indeksy do elementu najbardziej na lewo oraz na prawo */
    double pivot = arr[(l + r) / 2], /* wyznaczamy element podziałowy (pivot), względem któego będziemy porównywać wartości */
        t;                           /* przygotowujemy zmienną pomocniczą*/
    do
    {                          /* rozpoczynamy pętlę porównującą elemety do pivotu */
        while (arr[l] < pivot) /* dopóki lewy indeks zawiera liczbę mniejszą od pivotu (liczba jest "po dobrej stronie") */
            ++l;               /* to przesuwamy lewy indeks na kolejny od lewej element */
        while (pivot < arr[r]) /* dopóki prawy indeks zawiera liczbę większą od pivotu (liczba jest "po dobrej stronie") */
            --r;               /* to przesuwamy prawy indeks na kolejny od prawej element */
        /* powyższe pętle doprowadziły do sytuacji w której lewy i prawy indeks wskazują na elementy które są "po złej stronie",
           więc można je zamienić ze sobą miejscami, aby znalazły się " po dobrej stronie"
           albo element wskazywany przez lewy indeks jest po prawej stronie elementu wskazywanego przez prawy indeks,
           wtedy niczego nie zamieniamy, a kończymy pętlę*/
        if (l <= r)
        {                    /* jeśli jest to sytuacja w której możemy zamienić, to zamieniamy elementy miejscami */
            t = arr[l];      /* w zmiennej pomocniczej zapamiętujemy wartość lewego elementu */
            arr[l] = arr[r]; /* do lewego elemetu przepisujemy wartość prawego elementu */
            arr[r] = t;      /* do prawego element przepisujemy zapamiętaną wartość lewego elementu */
            ++l;
            --r; /* przesuwamy obydwa indeksy na koleje - odpowiednio od prawej i od lewej - elementy */
        }
    } while (l <= r); /* jeśli jest to sytuacja w której indeksy są w odpowiedniej kolejności, wykonujemy pętlę ponownie */
    if (l < end)
        quicksort(arr, l, end); /* Jeśli lewy indeks nie jest na końcu tablicy, to należy posortować pozostałą prawą część tablicy */
    if (beg < r)
        quicksort(arr, beg, r); /* Jeśli prawy indeks nie jest na początku tablicy, to należy posortować pozostałą lewą część tablicy */
}

/*
    Znajduje medianę elementów kolumny.
    Używany jest algorytm, który znajduje medianę w posortowanym zbiorze,
    ze względu na to, że chcemy zwrócić medianę, a bardziej zaawansowane
    algorytmy zwracają medianę górną w przypadku parzystych liczebności zbioru,
    zamiast średniej dwóch środkowych elementów.
    arr - tablica z danymi
    len - długośc tablicy
    Zwraca medianę elementów tablicy (arr)
*/
double median_column(double *arr, int len)
{
    /* tworzymy tablicę tymczasową, w której będziemy przechowywać wszystkie
       dane z kolumny, aby przekazać je do funkcji sorującej */
    double *array = (double *)malloc(sizeof(double) * len);
    double result = 0;            /* przygotowujemy zmienną do zapisania wyniku, po wyczyszczeniu pamięci */
    for (int i = 0; i < len; ++i) /* dopóki indeks jest mniejszy od liczby wierszy */
        array[i] = arr[i];        /* przepisujemy i-ty element z macierzy do tablicy*/

    quicksort(array, 0, len - 1);                           /* sortujemy tablicę dla zakresu od pierwszego do ostatniego elementu */
    if (len % 2 == 1)                                       /* dla nieparzystej liczności zbioru*/
        result = array[len / 2];                            /* mediana jest środkowym elementem */
    else                                                    /* dla parzystej liczności zbioru*/
        result = (array[len / 2] + array[len / 2 - 1]) / 2; /* mediana jest środkowym elementem */
    free(array);                                            /* zwalniamy miejsce w pamięci */
    return result;                                          /* zwracamy medianę */
}

/*
    wyświetla macierz współczynników Pearsona
    w postaci sformatowanej tabeli
    arr  - macierz
    size - liczba wierszy
*/
void display_pearson(double **arr, int size)
{
    int i, j;   /* przygotuj zmienne do iteracji */

	printf("\t\tWspolczynniki korelacji Pearsona\n\n param |"); /* nagłówek tabeli */
    for (j = 1; j <= size; ++j)     /* przygotuj wiersz nagłówkowy */
        printf("       %3d |", j);
    printf("\n-------+");              /* pozioma linia */
    for (j = 0; j < size; ++j)
        printf("-----------+");
    printf("\n");

    for (i = 0; i < size; ++i)      /* wyświetl właściwą część tabeli */
    {
        printf("   %3d | ", i+1); /* numer wiersza */
        for (j = 0; j < size; ++j)  /* dane w danym wierszu */
            printf("%9lf | ", arr[j][i]);
        printf("\n-------+");          /* pozioma linia */
        for (j = 0; j < size; ++j)
            printf("-----------+");
        printf("\n");               /* koniec wiersza */
    }
}

/*
    --- Punkt wejściowy programu ---
*/
int main(int argc, char *argv[])
{
    /*
        deklaracja macierzy z danymi
        format: data[numer_kolumny][numer_elementu]
        aby łatwiej przekazywać kolumny jako argumenty funkcji
    */
    double **data;
    double **pearson;                                    /* macierz korelacji Pearsona */
    char *file_name = (char *)malloc(sizeof(char) * 50); /* deklaracja stringa z nazwą pliku */
    int i, j,                                            /* deklaracja zmiennych potrzebnych do pętli */
        rows = 0,                                        /* rzeczywista liczba wierszy w pliku */
        pearson_size = COL-1;                            /* rozmiar macierzy współczynników Pearsona */


    /* -- ustalanie nazwy pliku wejściowego -- */

    if (argc > 1)
        strcpy(file_name, argv[1]); /* Jako pierwszy argument możemy podać nazwę pliku który chcemy wczytać */
    else
        strcpy(file_name, FILENAME); /* jeśli go nie podamy, nazwa zostaje domyślna */


    /* -- otwieranie pliku -- */

    FILE *input = fopen(file_name, "r"); /* otwarcie pliku w celu wczytania danych */
    if (input == NULL)
    { 
        /* jeśli nie udało się odczytać pliku, kończymy program */
        printf("Nie udalo sie otworzyc pliku %s\n", file_name);
        free(file_name);      /* zwalniamy string z nazwą pliku */
        return EXIT_FAILURE;  /* zwracamy kod błędu (1) */
    }
    printf("Odczytywanie danych z pliku: %s\n", file_name);
    free(file_name);          /* zwalniamy string z nazwą pliku, nie będzie już potrzebny */


    /* -- przygotowanie macierzy -- */

    /* dane rozmiaru COL x ROW */
    data = (double **)malloc(sizeof(double *) * COL);     /* alokacja pamięci kolumn */
    for (i = 0; i < COL; ++i)                             /* dla każdej kolumny */
        data[i] = (double *)malloc(sizeof(double) * ROW); /* alokacja wierszy */

    /* współczynniki Pearsona rozmiaru (COL-1) x (COL-1) - pierwszą kolumnę pomijamy przy obliczeniach */
    pearson = (double **)malloc(sizeof(double *) * pearson_size);     /* alokacja pamięci kolumn */
    for (i = 0; i < pearson_size; ++i)                                /* dla każdej kolumny */
        pearson[i] = (double *)malloc(sizeof(double) * pearson_size); /* alokacja wierszy */


    /* -- wczytywanie danych z pliku -- */

    for (i = 0; i < ROW && !feof(input); ++i) /* wczytuj linię z pliku aż dojdzie do końca pliku lub ustalonego limitu */
    { 
        for (j = 0; j < COL; j++)             /* wczytaj każdą kolumnę w danym wierszu */
        { 
            /* spróbuj wczytać kolejny element;
               jeśli nie udało się (fscanf zwróciło -1)
               to pomiń tę linię */
            if (fscanf(input, "%lf", &(data[j][i])) == -1)
            {
                --i;
                break;
            }
        }
    }
    rows = i;       /* zapamiętaj liczbę wczytanych wierszy */
    printf("Wczytano %d wierszy\n\n", rows);
    fclose(input);  /* zamknięcie pliku */


    /* -- wykonywanie obliczeń --*/

    for (i = 1; i < COL; ++i)
    { 
        /* Wykonaj obliczenia dla każdej kolumny i zapresentuj wynik*/
        printf("Kolumna %d :\n", i);
        printf("Suma:              %15lf\n",   sum_column               (data[i], rows)); /* oblliczenie sumy      */
        printf("Srednia:           %15lf\n",   average_column           (data[i], rows)); /* oblliczenie średniej  */
        printf("Wariancja:         %15lf\n",   variance_column          (data[i], rows)); /* oblliczenie wariancji */
        printf("Odch. standardowe: %15lf\n",   standard_deviation_column(data[i], rows)); /* oblliczenie odchylenia standardowego */
        printf("Maksimum:          %15lf\n",   max_column               (data[i], rows)); /* oblliczenie maksimum  */
        printf("Minimum:           %15lf\n",   min_column               (data[i], rows)); /* oblliczenie minimum   */
        printf("Mediana:           %15lf\n\n", median_column            (data[i], rows)); /* oblliczenie mediany   */

        for (j = i; j < COL; ++j) /* przy okazji policz wszystkie współczynniki Pearsona */
          /*
            możemy wykorzystać fakt, że macierz którą chcemy otrzymać będzie symetryczna,
            stąd wykonujemy obliczenia tylko dla około połowy par współczynników,
            a odpowiednie wyniki wpisujemy do dwóch komórek
         */
            pearson[j - 1][i - 1] = pearson[i - 1][j - 1] = 0;//gsl_stats_correlation(data[i], 1, data[j], 1, rows);
    }

    display_pearson(pearson, pearson_size); /* wyświetlamy macierz współczynników Pearsona */


    /* -- zwalnianie pamięci -- */

    for (i = 0; i < COL; ++i) /* zwalniamy pamięć wszystkich kolumn danych*/
        free(data[i]);
    free(data); /* zwalniamy pamięć dla wierszy */

    for (i = 0; i < pearson_size; ++i) /* zwalniamy pamięć wszystkich wierszy współczynników korelacji Pearsona*/
        free(pearson[i]);
    free(pearson); /* zwalniamy pamięć dla kolumn */

    return EXIT_SUCCESS; /* kończymy program z kodem sukcesu (0) */
}