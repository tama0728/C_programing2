#include <stdio.h>

int main(){
    char *a[] = {"apple", "pear", "banana"};
    printf("%c\n", (*++a)[0]); 
    return 0;
}
