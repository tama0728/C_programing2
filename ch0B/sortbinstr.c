#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char str[20];

int compare(const void *p, const void *q)
{
    return (strcmp((char *)p, (char *)q));
}

int main(void)
{
    char s[][10] = {"apple", "orange", "banana", "melon", "grape"};

    int num = sizeof(s) / sizeof(s[0]);
    printf("num is %d\n", num);
    int i;
    for (i = 0; i < num; ++i)
        printf("%s ", s[i]);
    printf("\n");

    qsort(s, num, sizeof(s[0]), compare);

    for ( i = 0; i < num; i++)
        printf("%s ", s[i]);
    printf("\n");

    char *found;
    char *key = "orange";
    if ((found = (char *)bsearch(key, s, num, sizeof(s[0]), compare)) != NULL)
        printf("Found key is %s.\n", found);
    else
        printf("There is no %s in List.\n", key);

    key = "opp";
    if ((found = (char *)bsearch(key, s, num, sizeof(s[0]), compare)) != NULL)
        printf("Found key is %s.\n", found);
    else
        printf("There is no %s in List.\n", key);
    return 0;
}
