#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    int c, n1, nw, nc, state;

    state = OUT;
    n1 = nw = nc = 0;
    while ((c = getchar()) != EOF){
        ++nc;       //문자가 들어오면 글자수 +1
        if (c == '\n')      //개행문자가 들어올 경우 줄수를 1 더한다
            ++n1;
        if (c == ' ' || c == '\n' || c == '\t')     //공백 개행 탭 인경우 단어 +1
            state = OUT;
        else if (state == OUT){
            state = IN;
            ++nw;
        }
    }
    printf("\t%d\t%d\t%d\n", n1, nw, nc);
    return 0;
}
