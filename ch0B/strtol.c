//
// Created by 김동윤 on 2023/05/22.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *s = "122";
    long l;

    l= strtol(s, NULL, 3);
    printf("%ld %x %o\n", l, l, l);

    return 0;
}
