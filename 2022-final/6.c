//
// Created by 김동윤 on 6/17/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tn{
    char *w;
    struct tn *l, *r;
};

struct tn *add(struct tn *p, char *w){
    if(p == NULL){
        p = (struct tn *)malloc(sizeof(struct tn));
        p->w = w;
        p->l = p->r = NULL;
    } else if(strcmp(w, p->w) < 0){
        p->l = add(p->l, w);
    } else {
        p->r = add(p->r, w);
    }
    return p;
}

void tprint(struct tn *p){
    if(p != NULL){
        printf("%s\n", p->w);
        tprint(p->l);
        tprint(p->r);
    }
}

int main(void) {
    char *str[] = {"This", "is", "a", "test", "string", "for", "add", "and", "print"};
    struct tn *r = NULL;

    int num = (int)(sizeof(str) / sizeof(char *));

    for (int i = 0; i < num; ++i) {
        r = add(r, str[i]);
    }
    tprint(r);
    return 0;
}
