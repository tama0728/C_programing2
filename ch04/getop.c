#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t');   //공백이나 탭이면 다음 문자로 넘어감
    s[1] = '\0';
    if (!isdigit(c) && c != '.')    //숫자가 아니면 연산자로 간주
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));  //숫자면 다음 문자로 넘어감
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));  //소수점이면 다음 문자로 넘어감
    s[i] = '\0';            //문자열 끝에 널문자 추가
    if (c != EOF)
        ungetch(c);     //숫자가 아닌 문자를 버퍼에 저장
    return NUMBER;
}