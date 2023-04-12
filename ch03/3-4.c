//common divisor
#include <stdio.h>

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);

    int i = 1;
    while (i <= a && i <= b){   //a, b 중 작은 수까지만 검사
        if (a % i == 0 && b % i == 0)   //공약수
            printf("%d ", i);
        i++;
    }
    putchar('\n');
    return 0;
}
