#include <stdio.h>

int main(void) {
    int n, i = 2;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (n == 1){
        printf("1");
        return 0;
    }
    do {
        if (n % i == 0){
            n /= i;
            printf("%d * ", i);
        } else
            i++;
    } while (n != i);
    printf("%d\n", n);

    return 0;
}