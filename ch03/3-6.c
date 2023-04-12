//factorial
#include <stdio.h>

int main(void) {
    long factorial;             //int형으로 하면 12!부터 오버플로우 발생
    /*
    for (int i = 1; i < 21; ++i) {
        factorial = 1;
        for (int j = 2; j <= i; ++j) {
            factorial *= j;             //i~j까지 곱하기
        }
        printf("%2d! = %ld\n", i, factorial);
    }
    */
    factorial = 1;
    for (int i = 1; i < 21; ++i) {
        factorial *= i;                 //연속으로 구하는 경우 전 factorial값을 이용
        printf("%2d! = %ld\n", i, factorial);
    }
    return 0;
}
