#include <stdio.h>

void qsort(double v[], int left, int right){
    int i, last;
    void swap(double v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(double v[], int i, int j){
    double temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main(void) {
    double array[] = {1.1, 9.9, 2.2, 8.8, 3.3, 7.7, 4.4, 6.6, 5.5, 0.0};
    for (int i = 0; i < 10; ++i)
        printf("%.1f ", array[i]);
    printf("\n");
    qsort(array, 0, 9);
    for (int i = 0; i < 10; ++i)
        printf("%.1f ", array[i]);
    printf("\n");
    return 0;
}
