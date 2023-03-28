#include<stdio.h>

int main(){
    double fahr = 0, celsius;
    int step = 20;
    
    printf("fahrenheit\tcelsius \n");
    while(fahr < 201){                    //화씨 200도까지 반복
        celsius = (5.0/9.0) * (fahr-32.0);     //화씨를 섭씨로 변환
        printf("%.6f\t%.6f \n", fahr, celsius); 
        fahr += step;   //20씩 증가
    }
    return 0;
}

