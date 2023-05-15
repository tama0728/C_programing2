//
// Created by 김동윤 on 2023/05/09.
//

#include <stdio.h>

int main(void) {
    printf("%*.*s\n", 15, 10, "hello");
    printf("%15s\n", "hello");
    printf("%-15s\n", "hello");

    return 0;
}
