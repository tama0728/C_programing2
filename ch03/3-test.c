#include <stdio.h>

int dtoi(double d){
    return (int) d;
}

int main (){
    double a = 9, b = 10.0;
    printf("%d\n", (int)a/(int)b);
    return 0;
}