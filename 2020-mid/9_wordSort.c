#include <stdio.h>
#include <string.h>

#define WORDLEN_MAX 100
#define LINE_MAX 100

void swap(char v[][WORDLEN_MAX], int i, int j){
    if (i==j)
        return;
    char temp[WORDLEN_MAX];
    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

void sort(char array[][WORDLEN_MAX], int left, int right){
    int i, last;

    if (left >= right)
        return;
    swap(array, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; ++i)
        if (strcmp(array[i], array[left]) < 0)
            swap(array, ++last, i);
    swap(array, left, last);
    sort(array, left, last - 1);
    sort(array, last + 1, right);
}
    

int main(int argc, char *argv[]){
    int c, r = 0, n;
    char word[LINE_MAX][WORDLEN_MAX];
    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            if (c == 'r')
                r = 1;
    n = argc;
    for (int i = 0; argc-- > 0; i++)
        strcpy(word[i], *argv++);
    
    for (int j = 0; j < n; j++)
        printf("%s ", word[j]);
    printf("\n");
    sort(word, 0, n-1); 
    
    for (int j = 0; j < n; j++)
        if (r)
            printf("%s ", word[n - j - 1]);
        else
            printf("%s ", word[j]);
    printf("\n");
    return 0;
}
