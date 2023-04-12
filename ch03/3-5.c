//prime number
#include <stdio.h>

int main(void) {
    int max = 200;

    for (int n = 2; n <= max; n++){             //2부터 max까지 검사
        for (int i = 2; i <= n/2 + 1; ++i) {    //2부터 n/2 + 1까지 검사
            if (i != 2 && n % i == 0)       //i로 나누어 떨어지면 소수가 아님(2는 예외)
                break;
            if (i == n/2 + 1)               //i가 n/2 + 1까지 검사했는데 나누어 떨어지지 않았으면 소수
                printf("%d ", n);
        }
    }
    return 0;
}
