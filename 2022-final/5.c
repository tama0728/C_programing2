//
// Created by 김동윤 on 6/17/23.
//

#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("%li %li\n", sizeof(char ), sizeof(short));

    printf("%d %d\n", CHAR_MIN, CHAR_MAX);
    printf("%d\n", UCHAR_MAX);
    printf("%d %d\n", SHRT_MIN, SHRT_MAX);
    printf("%d\n", USHRT_MAX);
    return 0;
}