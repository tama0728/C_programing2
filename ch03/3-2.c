#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int getlin(char s[], int lim){
    int c, i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

double atof(char s[]){
    int val, power, i, sign;
    for (i = 0; isspace(s[i]); i++);    //공백 제거
    sign = (s[i] == '-') ? -1 : 1;         //부호 저장
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0; isdigit(s[i]); i++)   //정수부 저장
        val = 10 * val + (s[i] - '0');
    if(s[i] == '.')
        i++;
    for(power = 1; isdigit(s[i]); i++) {
        val = 10 * val + (s[i] - '0');      //소수부 저장
        power *= 10;                        //소수부 자릿수 저장
    }
    return sign * (double)val / power;      //전체 수에서 소수부를 나누어 소수로 변환
}

void calc(double a, char op, double b, int type){
    double result;
    switch (op){        //연산자에 따라 계산
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = (int) a % (int) b;
            break;
        default:
            printf("error: unknown operator\n");    //연산자가 아닌 경우
            return;
    }
    if (type)
        printf("%f\n", result);    //소수인 경우
    else
        printf("%d\n", (int)result);    //정수인 경우
}

int find(char s[]){
    int i;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == '.')        //소수인 경우
            return 1;
    return 0;
}


int main(){
    double a, b;
    char op, line[MAXLINE], temp1[MAXLINE], temp2[MAXLINE];
    int i, j;
    while (getlin(line, MAXLINE) > 0){
        for (i = 0; line[i] != ' '; i++)
            temp1[i] = line[i];     //전체문자열에서 첫 번째 수를 temp1에 저장
        temp1[i++] = '\0';
        a = atof(temp1);        //첫 번째 수 저장
        op = line[i++];
        for (j = 0; line[i] != '\n'; i++, j++)
            temp2[j] = line[i];     //전체문자열에서 두 번째 수를 temp2에 저장
        temp2[j] = '\0';
        b = atof(temp2);        //두 번째 수 저장
        calc(a, op, b, find(line));     //계산
    }
    return 0;
}
