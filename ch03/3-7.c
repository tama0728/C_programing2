//ASCII code
#include <stdio.h>

int main(void) {
    int c;
    for (int i = 33; i < 127; ++i) {    //ASCII code 33~126까지 출력
        c = i;
        printf("%3d %2X %c ", c, c, c); //10진수, 16진수, 문자
        if ((i-32) % 6 == 0)            //6개씩 출력
            putchar('\n');
    }
    putchar('\n');
    return 0;
}
