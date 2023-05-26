#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1024
#define path = "/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p1/data.txt"


typedef struct Tel{
    char name[30];
    char tel[20];
    char memo[40];
    struct Tel *next;
}Tel;

void printAll(struct Tel *head) {
    struct Tel *p = head;
    int n = 1;
    while (p != NULL) {
        printf("%d %s %s %s\n",n, p->name, p->tel, p->memo);
        p = p->next;
        n++;
    }
}

void saveTel(struct Tel *head) {
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    struct Tel *p = head;
    while (p != NULL) {
        fprintf(fp, "%s:%s:%s\n", p->name, p->tel, p->memo);
        p = p->next;
    }
    fclose(fp);
}

Tel *firstAdd(struct Tel *head, char *name, char *tel, char *memo){
    struct Tel *p = (struct Tel *) malloc(sizeof(struct Tel));
    strcpy(p->name, name);
    strcpy(p->tel, tel);
    strcpy(p->memo, memo);
    p->next = head;
    head = p;
    return head;
}

void addTel(struct Tel *head, char *name, char *tel, char *memo) {
    struct Tel *p = head;
    while (p->next != NULL && strcmp(name, p->next->name) > 0) {
        p = p->next;
    }
    struct Tel *q = (struct Tel *) malloc(sizeof(struct Tel));
    strcpy(q->name, name);
    strcpy(q->tel, tel);
    strcpy(q->memo, memo);
    q->next = p->next;
    p->next = q;
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
    printf("\n");
    if (n == 1)
        printf("no match found.\n");
    else
        printf("match found.\n");
}

void deleteTel(struct Tel *head, char *temp) {
    struct Tel *p = head, *q, *list[MAX];
    int n = 1;
    while (p != NULL) {
        if (strstr(p->name, temp) != NULL || strstr(p->tel, temp) != NULL || strstr(p->memo, temp) != NULL) {
            printf("%d %s %s %s\n",n, p->name, p->tel, p->memo);
            list[n-1] = p;
            n++;
        }
        p = p->next;
    }
    printf("which one? ");
    char num;
    num = getchar();
    if (isdigit(num) == 0 || num > n-1 || num < 1) {
        printf("wrong input.\n");
        exit(1);
    }
    int i = num - '0';
    p = list[i];
    if (p == head) {
        head = p->next;
        head->pre = NULL;
        free(p);
    } else {
        p->pre->next = p->next;
        p->next->pre = p->pre;
        free(p);
    }
}

Tel *init(Tel *head, char *buf, char *name, char *tel, char *memo){
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
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
        if (head == NULL)
            head = firstAdd(head, name, tel, memo);
//        else
//            addTel(head, name, tel, memo);
    }
    fclose(fp);
    return head;
}

int main(int argc, char *argv[]) {
    struct Tel *p, *q, *head = (struct Tel *) malloc(sizeof(struct Tel));
    char buf[MAX], name[30], tel[20], memo[40];

    head = init(head, buf, name, tel, memo);

    printAll(head);
    printf("\n");
    addTel(head, "Kim", "010-1234-5678", "학생");
    addTel(head, "Kes", "010-1234-5678", "학생");
    addTel(head, "Ccc", "010-1234-5678", "학생");
    addTel(head, "Zzz", "010-1234-5678", "학생");
    addTel(head, "Aaa", "010-1234-5678", "학생");
    printAll(head);
    printf("\n");

    searchTel(head, "Bae");
    searchTel(head, "학생");
    searchTel(head, "aaa");

    return 0;
}
