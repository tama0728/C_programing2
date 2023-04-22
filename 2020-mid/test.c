#include <stdio.h>
#include <string.h>

#define MAX 100

void swap(char v[][MAX], int i, int j)
{
    if (i == j)
	return;
    char temp[MAX];
    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

void sort(char v[][MAX], int left, int right)
{
    int i, last;
    if (left >= right)
	return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
	if (strcmp(v[i], v[left]) < 0)
	    swap(v, ++last, i);
    swap(v, left, last);
    sort(v, left, last - 1);
    sort(v, last + 1, right);
}

int main(int argc, char *argv[])
{
    int c, r = 0, n;
    char v[100][MAX];
    while (--argc > 0 && (*++argv)[0] == '-')
	    while (c = *++argv[0])
		    if (c == 'r')
			    r = 1;
    n = argc;
    for (int i = 0; argc-- > 0; i++)
	strcpy(v[i], *argv++);
    sort(v, 0, n - 1);

    for (int i = 0; i < n; i++)
	if (r)
	    printf("%s ", v[n - i - 1]);
    	else
	    printf("%s ", v[i]);
    printf("\n");
    return 0;
}

