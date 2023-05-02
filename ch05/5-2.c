#include <stdio.h>

int main(void) {
    int a[][3] = {{1, 2, 3},
                  {4, 5, 6},
                  {7, 8, 9}};
    int *pa[] = {a[0], a[1], a[2]};
    int *p = a[0];

    int i;
    for (i =  0; i < 3; i++)
        printf("%d %d %d\n", a[i][2-i], *a[i], *(*(a+i)+i));
    printf("\n");

    for (i = 0; i < 3; i++)
        printf("%d %d\n", *pa[i], p[i]);
    printf("\n");
    return 0;
}
