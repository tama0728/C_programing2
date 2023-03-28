#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF){
        printf("%c", c);
        }
        if (c == ' ' || c == '\t' || c == '\n') {
            printf("\n");
        }
    return 0;
}
