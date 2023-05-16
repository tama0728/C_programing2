#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab[] = {
        {"auto",     0},
        {"break",    0},
        {"case",     0},
        {"char",     0},
        {"const",    0},
        {"continue", 0},
        {"default",  0},
        {"do",       0},
        {"double",   0},
        {"else",     0},
        {"enum",     0},
        {"extern",   0},
        {"float",    0},
        {"for",      0},
        {"goto",     0},
        {"if",       0},
        {"int",      0},
        {"long",     0},
        {"register", 0},
        {"return",   0},
        {"short",    0},
        {"signed",   0},
        {"sizeof",   0},
        {"static",   0},
        {"struct",   0},
        {"switch",   0},
        {"typedef",  0},
        {"union",    0},
        {"unsigned", 0},
        {"void",     0},
        {"volatile", 0},
        {"while",    0}
};

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {       //버퍼에 저장된 문자가 있으면 그 문자를 반환하고, 없으면 getchar()로부터 문자를 읽어서 반환
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {   //버퍼에 문자를 저장
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

//단어를 입력받는 함수
int getword(char *word, int lim){
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; ++w)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int binsearch(char *word, struct key tab[], int n){
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high){
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid; //found
    }
}

int main(void) {

    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)   //단어를 입력받아서
        if (isalpha(word[0]))               //첫 글자가 알파벳이면
            //binsearch()를 호출하여 keytab[]에서 찾는다.
            if ((n = binsearch(word, keytab, sizeof(keytab) / sizeof(keytab[0]))) >= 0)
                keytab[n].count++;
    //keytab[]에 저장된 단어들을 출력한다.
    for (n = 0; n < sizeof(keytab) / sizeof(keytab[0]); n++)
        if (keytab[n].count > 0)    //단어가 1번 이상 나왔으면
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}
