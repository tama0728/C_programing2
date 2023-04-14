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
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0; isdigit(s[i]); i++)
        val = 10 * val + (s[i] - '0');
    if(s[i] == '.')
        i++;
    for(power = 1; isdigit(s[i]); i++) {
        val = 10 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * (double)val / power;
}

void calc(double a, char op, double b, int type){
    double result;
    switch (op){
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
            printf("error: unknown operator\n");
            return;
    }
    if (type)
        printf("%f\n", result);
    else
        printf("%d\n", (int)result);

}

int find(char s[]){
    int i;
    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == '.')
            return 1;
    return 0;
}


int main(){
    double a, b, typeA, typeB;
    char op, line[MAXLINE], temp1[MAXLINE], temp2[MAXLINE];
    int i, j;
    while (getlin(line, MAXLINE) > 0){
        for (i = 0; line[i] != ' '; i++)
            temp1[i] = line[i];
        temp1[i++] = '\0';
        a = atof(temp1);
        op = line[i++];
        for (j = 0; line[i] != '\n'; i++, j++)
            temp2[j] = line[i];
        temp2[j] = '\0';
        b = atof(temp2);
        calc(a, op, b, find(line));
    }
    return 0;
}
