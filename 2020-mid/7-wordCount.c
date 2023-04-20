//
// Created by 김동윤 on 2023/04/19.
//

#include <stdio.h>
#define MAXLINE 100


int main(void) {
    char line[MAXLINE];
    int c, alpa[27] = {0};
    while ((c = getchar()) != EOF){
        if (c >= 65 && c < 65+26)
            alpa[c - 65]++;
        else if (c >= 97 && c < 97+26)
            alpa[c - 97]++;
        else
            alpa[26]++;
    }
    for (int i = 0; i < 26; ++i) {
        if (alpa[i] != 0)
            printf("%c/%c count : %d\n", i + 65, i + 97, alpa[i]);
    }
    if (alpa[26] != 0)
        printf("Others : %d", alpa[26]);
    return 0;
}
