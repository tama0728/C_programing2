#include <stdio.h>

void dtob(int n){
    if(n>1) dtob(n/2);  //n이 1보다 클때 dtob(n/2)호출
    printf("%d", n%2);  //그리고 2로 나눈 나머지 출력
}

int main(){
    int decimal;
    printf("십진수를 입력하세요: ");
    scanf("%d", &decimal);
    dtob(decimal);
    printf("\n");
    return 0;
}
