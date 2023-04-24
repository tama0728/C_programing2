#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
#define ALLOCSIZE 1000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int getlin(char s[], int lim){
    int c, i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

char *alloc(int n){
    if (allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

int readlines(char lineptr[][ALLOCSIZE], int maxlines){
    int len, nlines = 0;
    char *p, line[MAXLINE];
    while ((len = getlin(line, MAXLINE)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else{
            line[len-1] = '\0';
            strcpy(lineptr[nlines++], line);
        }
    return nlines;
}

void writelines(char lineptr[][ALLOCSIZE], int nlines){
    for (int i = 0; i < nlines; ++i) {
        printf("%s\n", lineptr[i]);
    }
}

int main(void){
    char lineptr[MAXLINE][ALLOCSIZE];
    int n = readlines(lineptr, MAXLINE);
    writelines(lineptr, n);
    return 0;
}