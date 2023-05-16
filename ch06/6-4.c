#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void){
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mstrdup(char *s){
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

struct tnode *addtree(struct tnode *p, char *w){
    int cond;

    if (p == NULL) {    //tree가 비어있으면
        p = talloc();
        p->word = mstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)    //tree에 이미 존재하는 단어면
        p->count++;
    else if (cond < 0)      //tree에 존재하는 단어보다 작으면
        p->left = addtree(p->left, w);
    else                    //tree에 존재하는 단어보다 크면
        p->right = addtree(p->right, w);
    return p;
}

//tree를 순회하면서 단어를 출력
void treeprint(struct tnode *p){
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

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
    int c, getch(void);
    void ungetch(int);
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

int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;    //tree 초기화
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))   //단어가 아닌 문자는 건너뜀
            root = addtree(root, word);     //tree에 단어 추가
    treeprint(root);    //tree를 순회하면서 단어를 출력
    return 0;
}
