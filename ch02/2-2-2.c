#include <stdio.h>

int main(){
    int c, state = 0;
    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c == ' ' || c == '\t') {
            putchar('\n');
        }
    }
    return 0;
}
