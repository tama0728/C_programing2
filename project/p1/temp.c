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
    printf("%d\n", isdigit('1'));
    return 0;
}
