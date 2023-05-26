//
// Created by 김동윤 on 2023/05/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int mstrcmp(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int main(void) {
    char *str = "\n";
    char *ptr = strtok(str, "\n");
    while (ptr != NULL) {
        printf("%s", ptr);
        ptr = strtok(NULL, "\n");
    }
    return 0;
}
