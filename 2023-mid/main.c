#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_str(const void *a, const void *b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

int cmp_num(const void *a, const void *b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return atoi(*ia) - atoi(*ib);
}

int main(int argc, char *argv[]) {
    int use_numeric_order = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        use_numeric_order = 1;
    }

    int num_strings = argc - use_numeric_order - 1;
    char **strings = malloc(num_strings * sizeof(char *));
    for (int i = 0; i < num_strings; i++) {
        strings[i] = argv[i + use_numeric_order + 1];
    }

    if (use_numeric_order) {
        qsort(strings, num_strings, sizeof(char *), cmp_num);
    } else {
        qsort(strings, num_strings, sizeof(char *), cmp_str);
    }

    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }

    free(strings);
    return 0;
}
