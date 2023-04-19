#include <stdio.h>
#include <string.h>

#define ELEMENTS 7
#define NAMELEN 10

void swap(char v[][NAMELEN], int i, int j){
    if (i == j)
        return;
    char temp[NAMELEN];
    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

void sort(char array[][NAMELEN], int left, int right) {
    int i, last;

    if (left >= right)
        return;
    swap(array, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i)
        if (strcmp(array[i], array[left]) < 0)
            swap(array, ++last, i);
    swap(array, left, last);
    sort(array, left, last - 1);
    sort(array, last + 1, right);
}

int main(void) {
    char array[ELEMENTS][NAMELEN] = {"kim", "lee", "park", "choi", "jung", "kang", "cho"};
    for (int i = 0; i < ELEMENTS; ++i)
        printf("%s ", array[i]);
    printf("\n");
    sort(array, 0, ELEMENTS - 1);
    for (int i = 0; i < ELEMENTS; ++i)
        printf("%s ", array[i]);
    printf("\n");
    return 0;
}
