#include <stdio.h>
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void) {       //버퍼에 저장된 문자가 있으면 그 문자를 반환하고, 없으면 getchar()로부터 문자를 읽어서 반환
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {   //버퍼에 문자를 저장
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}