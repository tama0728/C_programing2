#include <stdio.h>
#include <math.h>   //pow함수를 위해 사용

int htoi(char s[]){
    int i = 0, j = 0, n = 0, temp;

    while(s[i] != '\0'){    //s의 길이 구하기(string.h 에 있는 strlen 구현)
        i++;
    }
    while (j < i){
        if(s[j] >= '0' && s[j] <= '9')
            temp = s[j] - '0';          //0~9인 경우 숫자 0~9로 변경
        else if (s[j] >= 'A' && s[j] <= 'F')
            temp = s[j] - 'A' + 10;     //A~F인 경우 숫자 10~15로 변경
        else if (s[j] >= 'a' && s[j] <= 'f')
            temp = s[j] - 'a' + 10;     //소문자인 경우도 변경
        n += (int)pow(16, i - j - 1) * temp;
        j++;
    }

    return n;
}

int main(){
    char h[] = "12AF";

    printf("%s\n", h);
    printf("%x\n", htoi(h));
    printf("%d\n", htoi(h));

    return 0;
}
