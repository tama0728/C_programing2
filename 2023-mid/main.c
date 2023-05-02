#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

int main(){
    char s1[10][8] = {
            "india", "delta", "bravo", "kilo", "alfa",
            "echo", "hotel", "juliett", "golf", "charlie"
    };
    qsort(s1, sizeof(s1)/ sizeof(s1[0]), sizeof(s1[0]), compare);
    for (int i = 0; i < 10; i++)
    {
        printf("%s ", s1[i]);
    }
    return 0;
}
