#include <stdio.h>

int i = 10;

void f(){
    int i = 1;
    printf("i in f() is %d\n", i++);
}

void s(){
    static int i = 100;
    printf("i in s() is %d\n", i++);
}

int main(){
    for (int j = 0; j <3; ++j){
        printf("i in main is %d\n", i++);
        f();
        s();
    }
    return 0;
}
