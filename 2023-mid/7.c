#include <stdio.h>
long fac(int n){    /*long타입으로 한 이유는 int의 최대 크기보다 큰 수가 나오기때문에*/
    if (n==1)   //n=1일 경우 1반환
        return 1;
    return n*fac(n-1); //아닌경우 n*fac(n-1)반환
}
int main(){
    for (int i=1;i<21;i++)
        printf("%ld\n", fac(i));
    return 0;
}
