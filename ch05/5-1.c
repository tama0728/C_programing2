#include <stdio.h>

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int *p = a;
    int i;

    //print with a[i] and for()
    for (i = 0; i < 5; ++i)
        printf("%d ", a[i]);
    printf("\n");

    //print with *p and while()
    i = 0;
    while (i < 5){
        printf("%d ", *p++);
        i++;
    }
    printf("\n");
    return 0;
}
