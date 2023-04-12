#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int getlin(char s[], int lim){
    int c, i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

double atof(char s[]){
    int val, power, i;

    for (i = 0; isspace(s[i]); i++);

    for (val = 0; isdigit(s[i]); i++)
        val = 10 * val + (s[i] - '0');
    if(s[i] == '.')
        i++;
    for(power = 1; isdigit(s[i]); i++) {
        val = 10 * val + (s[i] - '0');
        power *= 10;
    }
    return (double) val / power;
}

//double calc(double a, char op, double b){
//    switch (op){
//        case '+':
//            return a + b;
//        case '-':
//            return a - b;
//        case '*':
//            return a * b;
//        case '/':
//            return a / b;
//        case '%':
//            return (int) a % (int) b;
//        default:
//            return 0;
//    }
//}


int main(){
    double a, b;
    char op, line[MAXLINE], temp1[MAXLINE];
    int i, j;
    while (getlin(line, MAXLINE) > 0){
        for (i = 0; line[i] != ' '; i++)
            temp1[i] = line[i];
        temp1[i++] = '\0';
        a = atof(temp1);
        op = line[i++];
        for (j = 0; line[i] != '\n'; i++, j++)
            temp1[j] = line[i];

        temp1[++j] = '\0';
        b = atof(temp1);

//        printf("%g\n", calc(a, op, b));
    }
    return 0;
}
