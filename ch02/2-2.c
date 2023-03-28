#include <stdio.h>

int main() {
    char temp[50] = "";     //입력받은 문자를 저장할 공간
    int i = 0, c;
    while ((c = getchar()) != EOF){
        if (c == '\n'){     // 엔터를 입력한 경우 출력
            printf("%s\n", temp);           //temp 출력
            for (int j = 0; j < i+1; j++){  //temp 문자열 초기화
                temp[j] = 0;
            }
            i = 0;
            continue;
        }

        if (c == ' ' || c == '\t'){     //공백이나 탭이 입력된 경우 개행문자로 변경해 저장
            c = '\n';
        }
        temp[i] = c;
        i++;
    }
    return 0;
}
