#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1024
#define data "/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p1/data.txt"
#define help "/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p1/help.txt"

typedef struct Tel{
    char name[30];
    char tel[20];
    char memo[40];
    struct Tel *next;
}Tel;

Tel *insert(Tel *head, char *name, char *tel, char *memo) {
    Tel *p = head;
    if (p == NULL) {
        head = (Tel *) malloc(sizeof(Tel));
        strcpy(head->name, name);
        strcpy(head->tel, tel);
        strcpy(head->memo, memo);
        head->next = NULL;
        return head;
    }
    while (p->next != NULL && strcmp(name, p->next->name) > 0) {
        p = p->next;
    }
    Tel *q = (Tel *) malloc(sizeof(Tel));
    strcpy(q->name, name);
    strcpy(q->tel, tel);
    strcpy(q->memo, memo);
    q->next = p->next;
    p->next = q;
    return head;
}

Tel *init(Tel *head){
    FILE *fp = fopen(data, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    char buf[MAX], name[30], tel[20], memo[40];
    while (fgets(buf, MAX, fp) != NULL){
        char *ptr = strtok(buf, ":\n");
        int i = 0;
        while (ptr != NULL) {
            if (i == 0)
                strcpy(name, ptr);
            else if (i == 1)
                strcpy(tel, ptr);
            else
                strcpy(memo, ptr);
            ptr = strtok(NULL, ":\n");
            i++;
        }
        head = insert(head, name, tel, memo);
    }
    fclose(fp);
    return head;
}

void searchTel(struct Tel *head, char *temp){
    struct Tel *p = head;
    int n = 1;
    while (p != NULL) {
        if (strstr(p->name, temp) != NULL || strstr(p->tel, temp) != NULL || strstr(p->memo, temp) != NULL) {
            printf("%d %s %s %s\n",n, p->name, p->tel, p->memo);
            n++;
        }
        p = p->next;
    }
    if (n == 1)
        printf("no match found.\n");
    else
        printf("match found.\n");
}

void add(char *name, char *tel, char *memo) {
    printf("add? [Y/N]: ");
    int c = getchar();
    if (c != 'Y' && c != 'y') {
        printf("add canceled.\n");
        exit(0);
    }

    FILE *fp = fopen(data, "a");
    fprintf(fp, "%s:%s:%s\n", name, tel, memo);
    fclose(fp);
    printf("add completed.\n");
    exit(0);
}

void save(struct Tel *head) {
    FILE *fp = fopen(data, "w");
    struct Tel *p = head;
    while (p != NULL) {
        fprintf(fp, "%s:%s:%s\n", p->name, p->tel, p->memo);
        p = p->next;
    }
    fclose(fp);
    exit(0);
}

void delete(struct Tel *head, char *key) {
    struct Tel *p = head;
    int n = 1, i = 0, tmep[MAX] = {0};
    while (p != NULL) {
        if (strstr(p->name, key) != NULL || strstr(p->tel, key) != NULL || strstr(p->memo, key) != NULL) {
            printf("%d %s %s %s\n", n, p->name, p->tel, p->memo);
            tmep[n-1] = i;
            n++;
        }
        i++;
        p = p->next;
    }

    if (n == 1) {
        printf("no match found.\n");
        exit(0);
        }
    printf("which one? ");
    int num = getchar();

    if (!isdigit(num) || num - '0' > n - 1 || num - '0' < 1) {
        printf("wrong input.\n");
        exit(0);
    }
    num = tmep[num - '1'];
    p = head;
    for (int j = 0; j < num; ++j)
        p = p->next;
    if (p == head) {
        head = head->next;
        free(p);
    } else {
        struct Tel *q = head;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
        free(p);
    }
    save(head);
}

void printAll(Tel *head) {
    Tel *p = head;
    int n = 1;
    while (p != NULL) {
        printf("%d %s %s %s\n",n, p->name, p->tel, p->memo);
        p = p->next;
        n++;
    }
}

int main(int argc, char *argv[]) {
    struct Tel *head = NULL;

    // 옵션과 문자가 없는 경우 help.txt 출력
    if (argc == 1) {
        char buf[MAX];
        FILE *fp = fopen(help, "r");
        while (fgets(buf, MAX, fp) != NULL)
            printf("%s", buf);
        fclose(fp);
        exit(0);
    }

    //옵션이 없고 문자만 있는 경우 search 실행
    if ((*++argv)[0] != '-') {
        head = init(head);
        searchTel(head, *argv);
        exit(0);
    }

    //옵션과 문자가 있는 경우
    if ((*argv)[0] == '-') {
        switch ((*argv)[1]) {
            case 'a':
                head = init(head);
                add(*++argv, *++argv, *++argv);
                break;
            case 'd':
                head = init(head);
                delete(head, *++argv);
                break;
            case 'l':
                head = init(head);
                printAll(head);
                break;
            default:
                printf("wrong option.\n");
                exit(0);
        }
    } else {
        printf("wrong option.\n");
        exit(1);
    }
}