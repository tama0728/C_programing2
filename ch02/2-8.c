#include <stdio.h>

int main(){
    int i = 0X0f;
    int j = 0X14;

    printf("i & j = %X\n", i&j);
    printf("i | j = %X\n", i|j);
    printf("i ^ j = %X\n", i^j);
    printf("~(i | j) = %X\n",~(i|j));
    printf("i<<2 = %X\n", i<<2);
    printf("i>>3 = %X\n", i>>3);

    return 0;
}
