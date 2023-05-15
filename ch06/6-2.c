#include <stdio.h>

int main(void) {
    struct node {
        int len;
        char *str;
    };
    struct node a[] = {5, "hello", 10, "world"};
    struct node *p = a;

    printf("a[0].len is %d\n", a[0].len);   //첫번째 노드의 len
    printf("p->len is %d\n", p->len);       //첫번째 노드의 len
    printf("p->str is %s\n", p->str);       //첫번째 노드의 str
    printf("*p++->str is %c\n", *p++->str); //첫번째 노드의 str의 첫번째 문자 그리고 p를 증가시킴
    printf("p->len is %d\n", p->len);       //두번째 노드의 len
    printf("p->str is %s\n", p->str);       //두번째 노드의 str

    return 0;
}
