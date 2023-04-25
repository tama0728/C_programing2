#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WORDLEN_MAX 100
#define LINE_MAX 100

int getlin(char s[], int lim){
    int c, i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void swap(char v[][WORDLEN_MAX], int i, int j){
    if (i==j)
        return;
    char temp[WORDLEN_MAX];
    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

void sort(char array[][WORDLEN_MAX], int left, int right){
    int i, last;

    if (left >= right)
        return;
    swap(array, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; ++i)
        if (strcmp(array[i], array[left]) < 0)
            swap(array, ++last, i);
    swap(array, left, last);
    sort(array, left, last - 1);
    sort(array, last + 1, right);
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

void shellsort(double v[], int n){
    int gap, i, j;
    double temp;
    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; ++i)
            for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap){
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}


#define ALLOCSIZE 1000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n){
    if (allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n;
    } else
        return 0;
}