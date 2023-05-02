#include <stdio.h>
//#include <ctype.h>
#include <stdlib.h>
//double atof(char s[]){
//    int val, power, i, sign;
//    for (i = 0; isspace(s[i]); i++);    //공백 제거
//    sign = (s[i] == '-') ? -1 : 1;         //부호 저장
//    if (s[i] == '+' || s[i] == '-')
//        i++;
//    for (val = 0; isdigit(s[i]); i++)   //정수부 저장
//        val = 10 * val + (s[i] - '0');
//    if(s[i] == '.')
//        i++;
//    for(power = 1; isdigit(s[i]); i++) {
//        val = 10 * val + (s[i] - '0');      //소수부 저장
//        power *= 10;                        //소수부 자릿수 저장
//    }
//    return sign * (double)val / power;      //전체 수에서 소수부를 나누어 소수로 변환
//}

int main(int argc, char *argv[]){
    double  sum = 0;
    int n = argc - 1; //인자의 개수 저장
    while (argc-- > 0){
        sum += atof(*argv++);   //sum에 command-line arguments로 받은 숫자를 저장
    }
    printf("sum: %f\n", sum);
    printf("average: %f\n", sum/n);
    return 0;
}
