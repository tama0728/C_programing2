#include <stdio.h>
#include <string.h>

#define ELEMENTS 7
#define NAMELEN 10

void swap(char v[][NAMELEN], int i, int j){
    if (i == j)     // 두 원소가 같은 위치를 가리키면 교환할 필요가 없음
        return;
    char temp[NAMELEN];
    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

void sort(char array[][NAMELEN], int left, int right) {
    int i, last;

    if (left >= right)      // 원소가 1개인 경우
        return;
    swap(array, left, (left + right) / 2);      // 중간값을 피벗으로 선택
    last = left;
    for (i = left + 1; i <= right; ++i)             // 피벗을 제외한 나머지 원소들을 정렬
        if (strcmp(array[i], array[left]) < 0)      // 피벗보다 작은 원소들은 피벗의 오른쪽으로 이동
            swap(array, ++last, i);
    swap(array, left, last);                // 피벗을 중간으로 이동
    sort(array, left, last - 1);               // 피벗을 제외한 왼쪽 부분을 정렬
    sort(array, last + 1, right);               // 피벗을 제외한 오른쪽 부분을 정렬
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

