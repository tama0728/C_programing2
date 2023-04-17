#include <stdio.h>

int max(int i, int j, int k){
    int max = i;    //초기값
    if (j > max)    //j와 비교
        max = j;
    if (k > max)    //k와 비교
        max = k;
    return max;
}

int min(int i, int j, int k){
    int min = i;    //초기값
    if (j < min)    //j와 비교
        min = j;
    if (k < min)    //k와 비교
        min = k;
    return min;
}

int main(){
    int i = 10;
    int j = 20;
    int k = -30;
 
    printf("Min value is %d\n", min(i, j, k));
    printf("Max value is %d\n", max(i, j, k));

    return 0;
}
