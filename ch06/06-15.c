//
// Created by 김동윤 on 2023/05/01.
//

#include <stdio.h>

struct word{
    int len;
    char *str;
};

int main(void) {
    struct word *p;
    char *str = "hello";
    p->len = 5;
    p->str = str;
    printf("p->len %d\n", p->len);
    printf("++p->len %d\n", ++p->len);
    printf("++(p->len) %d\n", ++(p->len));
    printf("(++p)->len %d\n", (++p)->len);
    printf("(p++)->len %d\n", (p++)->len);
    printf("p->len %d\n", p->len);
//    printf("p->str %s\n", p->str);
    printf("*p->str %c\n", *p->str);
    printf("*p->str %c\n", *p->str++);
    printf("(*p->str)++ %c\n", (*p->str)++);
    printf("*p++->str %c\n", *p++->str);
    printf("p->str %s\n", p->str);
    return 0;
}
