#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 100
char *lineptr[MAXLINES];

char *alloc(int n){
    char *p;
    if ((p = malloc(n)) == NULL)
        printf("error: malloc failed\n");
    return p;
}

int mygetline(char s[], int lim){
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int nlines){
    int len;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= MAXLINES || (p = alloc(len)) == NULL)
            return -1;
        else{
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines){
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

int numcmp(char *s1, char *s2){
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        qsort((void **) lineptr, nlines-1, sizeof(lineptr[0]),(int (*)(const void *, const void *))(numeric ? numcmp : strcmp));
        
        printf("After sort.\n");
        writelines(lineptr, nlines);
        return 0;
    } else{
        printf("error: input too big to sort\n");
        return 1;
    }

    return 0;
}
