//
// Created by 김동윤 on 2023/04/20.
//

#include <stdio.h>

int main(void) {
    int a[][5] = {  { 1, 2, 3, 4, 5 },
                    { 6, 7, 8, 9, 10 },
                    { 11, 12, 13, 14, 15 },
                    { 16, 17, 18, 19, 20 },
                    { 21, 22, 23, 24, 25 }};

    double table[7][7] = {0};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            table[i][j] = a[i][j];
            table[i][5] += a[i][j];
            table[5][i] += a[j][i];
        }
        table[i][6] = table[i][5] / 5;
        table[6][i] = table[5][i] / 5;
        table[5][5] += table[5][i];
    }
    table[6][6] = table[5][5] / 5;

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (table[i][j] == 0.0)
                printf("       ");
            else
                printf("%7.2f", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}
