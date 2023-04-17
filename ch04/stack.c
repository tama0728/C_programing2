#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];
void push(double f) {
    if (sp < MAXVAL)    //스택이 가득 차지 않았으면
        val[sp++] = f;
    else                //스택이 가득 찼으면
        printf("error: stack full, can't push %g\n", f);
}
double pop(void) {
    if (sp > 0)     //스택이 비어있지 않으면
        return val[--sp];
    else {          //스택이 비어있으면
        printf("error: stack empty\n");
        return 0.0;
    }
}
