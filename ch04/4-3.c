#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));  //srand에 시간으로 seed값 변경
    for(int i = 0; i < 4; i++){
        printf("%3d", rand() % 10);
    }
    printf("\n");
    return 0;
}
