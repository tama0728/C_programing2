#include <stdio.h>
#include <string.h>

int  mystrlen(char *s) {
    int n;
    //널문자가 나올떼 까지 반복
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}

int main(void) {
    char *s[] = {"This is Lab5", "Easy C Programming", "Have fun"};

    printf("with strlen()\n");
    //배열의 원소 개수 구하기
    int n = (int)(sizeof(s) / sizeof(char *));
    for (int i = 0; i < n; ++i)
        printf("%s %d\n", s[i], (int)strlen(s[i]));
    printf("\n");

    printf("with mystrlen()\n");
    for (int i = 0; i < n; ++i)
        printf("%s %d\n", s[i], (int)mystrlen(s[i]));
    printf("\n");

    return 0;
}
