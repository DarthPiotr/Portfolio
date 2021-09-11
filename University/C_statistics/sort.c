#include <stdio.h>
#include <stdlib.h>

void quicksort(double* arr, int beg, int end) {
    int l = beg, r = end;
    double pivot = arr[(l + r) / 2], t;
    do {
        while (arr[l] < pivot) {
            ++l;
        }
        while (pivot < arr[r]) {
            --r;
        }
        if (l <= r) {
            t = arr[l];
            arr[l] = arr[r];
            arr[r] = t;
            ++l;
            --r;
        }
    } while (l <= r);
    if (l < end) quicksort(arr, l, end);
    if (beg < r) quicksort(arr, beg, r);
}

int display(double *arr){
    int i = 0;
    while(i < 5)
        printf("%lf ", arr[i++]);
    printf("\n");
}

int main(void){

    double *array = (double*)malloc(sizeof(double) * 5);
    array[0] = 0.124;
    array[1] = 12.234;
    array[2] = 22.554;
    array[3] = 1.22;
    array[4] = 3.777;
    display(array);
    quicksort(array, 0, 4);
    display(array);

    return 0;
}