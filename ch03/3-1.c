#include <stdio.h>

int main(){
    int a, b;
    printf("enter two integer : "); //두 정수 입력받기
    scanf("%d %d", &a, &b);
    int sub = a > b ? a-b : b-a;    //a와 b를 비교해 빼기연산 후 저장
    printf("subtract : %d\n", sub);
    return 0;
}
