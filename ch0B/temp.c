#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// str자료형 재정의 char[20] => str로 재정의
typedef char str[20];

// 비교알고리즘
int cmp(const void* a, const void *b)
{
    return strcmp((char*)a, (char*)b);
}

int main(void)
{
    str Array[] = { "asdf", "basdf", "casdf", "defaef", "feaef" }; // 오름차순으로 정렬되어있어야한다..
    char *Key = "asdf";
    str *position = (str*)bsearch(Key, Array, sizeof(Array) / sizeof(str), sizeof(str), cmp);

    if (position != NULL)
        printf("%s\n", position);
    else
        printf("fail\n");

    return 0;
}