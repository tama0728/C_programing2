#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1024
#define data "data.txt"
#define help "help.txt"

//전화번호부 구조체 링크드 리스트로 구현
typedef struct Tel{
    char name[30];
    char tel[20];
    char memo[40];
    struct Tel *next;
}Tel;

//동적 할당 전체 해제
void allFree(Tel *head) {
    Tel *p = head;
    while (p != NULL) {
        Tel *q = p->next;
        free(p);
        p = q;
    }
}

//리스트에 오름차순으로 추가
Tel *insert(Tel *head, char *name, char *tel, char *memo) {
    Tel *p = head;
    //리스트가 비어있을 때
    if (p == NULL) {
        head = (Tel *) malloc(sizeof(Tel));
        strcpy(head->name, name);
        strcpy(head->tel, tel);
        strcpy(head->memo, memo);
        head->next = NULL;
        return head;
    }
    //리스트가 비어있지 않을 때 오름차순으로 추가
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

//data.txt 에서 파일 읽어오기
Tel *init(Tel *head) {
    FILE *fp = fopen(data, "rt");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    char buf[MAX];
    while (fgets(buf, MAX, fp) != NULL){
        //파일에서 한 줄씩 읽어서 ':'와 '\n'을 기준으로 문자열을 나누고, 각각 name, tel, memo에 저장
        char name[30] = {0}, tel[20] = {0}, memo[40] = {0}, *ptr = strtok(buf, ":\n");
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
        //리스트에 추가
        head = insert(head, name, tel, memo);
    }
    fclose(fp);
    return head;
}

//key 값을 받아 해당 노드 찾기
void searchTel(struct Tel *head, char *temp){
    struct Tel *p = head;
    int n = 1;
    while (p != NULL) {
        //name, tel, memo에 key 값이 포함되어 있으면 출력
        if (strstr(p->name, temp) != NULL || strstr(p->tel, temp) != NULL || strstr(p->memo, temp) != NULL) {
            printf("%d %s %s %s\n",n, p->name, p->tel, p->memo);
            n++;
        }
        p = p->next;
    }
    //key 값이 없으면 no match found 출력
    if (n == 1)
        printf("no match found.\n");
    else
        printf("match found.\n");
}

//data.txt에 추가
void add(char *name, char *tel, char *memo) {
    printf("%s %s %s\n", name, tel, memo);
    printf("add? [Y/N]: ");
    int c = getchar();
    //Y 또는 y가 아니면 add 취소
    if (c != 'Y' && c != 'y') {
        printf("add canceled.\n");
        exit(0);
    }
    //data.txt의 가장 뒤에 추가
    FILE *fp = fopen(data, "at");
    fprintf(fp, "%s:%s:%s\n", name, tel, memo);
    fclose(fp);
    printf("add completed.\n");
}

//data.txt에 리스트에 있는 내용 저장
void save(struct Tel *head) {
    //data.txt의 내용을 모두 지우고 새로 저장
    FILE *fp = fopen(data, "wt");
    struct Tel *p = head;
    while (p != NULL) {
        fprintf(fp, "%s:%s:%s\n", p->name, p->tel, p->memo);
        p = p->next;
    }
    fclose(fp);
}

//리스트에서 삭제 후 data.txt에 저장
void delete(struct Tel *head, char *key) {
    struct Tel *p = head;
    int n = 1, i = 0, tmep[MAX] = {0};
    //key 값이 포함된 노드 찾기
    while (p != NULL) {
        if (strstr(p->name, key) != NULL || strstr(p->tel, key) != NULL || strstr(p->memo, key) != NULL) {
            printf("%d %s %s %s\n", n, p->name, p->tel, p->memo);
            tmep[n-1] = i;      //key 값이 포함된 노드의 인덱스 저장
            n++;
        }
        i++;
        p = p->next;
    }
    //key 값이 없으면 no match found 출력
    if (n == 1) {
        printf("no match found.\n");
        allFree(head);
        exit(0);
        }
    printf("which one? ");
    int num = getchar();
    //입력이 숫자가 아니거나 1~n-1 사이의 숫자가 아니면 wrong input 출력
    if (!isdigit(num) || num - '0' > n - 1 || num - '0' < 1) {
        printf("wrong input.\n");
        allFree(head);
        exit(0);
    }
    num = tmep[num - '1'];
    //num이 0이면  head를 다음 노드로 변경
    p == head;
    if (num == 0) {
        head = head->next;
        free(p);
    } else {
        //삭제할 노드의 이전 노드까지 이동
        for (int j = 0; j < num-1; ++j)
            p = p->next;
        struct Tel *temp = p->next;
        p->next = p->next->next;
        free(temp);
    }
    printf("delete completed.\n");
    //data.txt에 저장
    save(head);
}

//리스트 전체 출력
void printAll(Tel *head) {
    Tel *p = head;
    int n = 1;
    //리스트의 끝까지 이동하면서 출력
    while (p != NULL) {
        printf("%d %s %s %s\n",n, p->name, p->tel, p->memo);
        p = p->next;
        n++;
    }
}

int main(int argc, char *argv[]) {
    struct Tel *head = NULL;

    // 옵션과 문자가 없는 경우 help.txt 출력
    if (--argc == 0) {
        char buf[MAX];
        FILE *fp = fopen(help, "rt");
        while (fgets(buf, MAX, fp) != NULL)
            printf("%s", buf);
        fclose(fp);
        exit(0);
    }
    //옵션이 없고 문자만 있는 경우 search 실행
    if ((*++argv)[0] != '-') {
        head = init(head);
        searchTel(head, *argv);
        allFree(head);
        exit(0);
    }
    //옵션과 문자가 있는 경우
    if (argc > 0 && (*argv)[0] == '-') {
        switch ((*argv)[1]) {
            case 'a':
                add(*++argv, *++argv, *++argv);
                break;
            case 'd':
                head = init(head);
                delete(head, *++argv);
                allFree(head);
                break;
            case 'l':
                head = init(head);
                printAll(head);
                allFree(head);
                break;
            default:
                printf("wrong option.\n");
                exit(0);
        }
    } else {
        printf("wrong option.\n");
        exit(1);
    }
    return 0;
}
