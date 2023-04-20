//
// Created by 김동윤 on 2023/04/19.
//

#include <stdio.h>

int main(void) {
    for (int i = 0; i < 26; ++i) {
        printf("%c%c ", i+65, i+97);
        if (i % 6 == 5)
            printf("\n");
    }
    return 0;
}
