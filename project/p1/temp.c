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
    FILE *fp = fopen("/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p1/text.txt", "a");
    fprintf(fp, "hello world\n");
    fclose(fp);
    return 0;
}
