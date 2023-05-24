//
// Created by 김동윤 on 2023/05/22.
//

#include <stdio.h>
#include <string.h>

int main(void) {
    char s[] = "kim dong:010 9837: student";
    char *ptr;

    ptr = strtok(s, ": ");
    while (ptr != NULL){
        printf("%s\n", ptr);
        ptr = strtok(NULL, ": ");
    }

    return 0;
}
