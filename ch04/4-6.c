#include <stdio.h>

void swap(double v[], int i, int j){
    double temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(double v[], int left, int right){
    int i, last;

    if (left >= right)          // 원소가 1개인 경우
        return;
    swap(v, left, (left + right) / 2);  // 중간값을 피벗으로 선택
    last = left;
    for (i = left + 1; i <= right; ++i)      // 피벗을 제외한 나머지 원소들을 정렬
        if (v[i] < v[left])
            swap(v, ++last, i);         // 피벗보다 작은 원소들은 피벗의 오른쪽으로 이동
    swap(v, left, last);                // 피벗을 중간으로 이동
    qsort(v, left, last - 1);           // 피벗을 제외한 왼쪽 부분을 정렬
    qsort(v, last + 1, right);           // 피벗을 제외한 오른쪽 부분을 정렬
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

