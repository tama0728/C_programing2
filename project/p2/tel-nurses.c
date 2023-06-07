//
// Created by 김동윤 on 2023/06/02.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <form.h>
#include <locale.h>

#define MAX 1024
#define data "/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p2/data.txt"
#define help "/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p2/help.txt"
char *menu[] = {"help", "list", "search", "add", "delete", "exit"};

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

Tel *firstAdd(Tel *head, char *name, char *tel, char *memo){
    Tel *p = (Tel *) malloc(sizeof(Tel));
    strcpy(p->name, name);
    strcpy(p->tel, tel);
    strcpy(p->memo, memo);
    p->next = head;
    head = p;
    return head;
}

//리스트에 오름차순으로 추가
Tel *insert(Tel *head, char *name, char *tel, char *memo) {
    Tel *p = head;
    //리스트가 비었거나 첫 번째 노드보다 작을 때
    if (p == NULL || strcmp(name, head->name) < 0)
        return firstAdd(head, name, tel, memo);

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
    FILE *fp = fopen(data, "r");
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

//리스트 전체 출력
void printAll(Tel *head, int xMax) {
    Tel *p = head;
    int n = 1, j, max = 0;
    mvwprintw(stdscr, 1, xMax/3, "%3s  %-10s %-15s\t%s", "No", "Name", "Tel", "Memo");
    //리스트의 끝까지 이동하면서 출력
    while (p != NULL) {
        mvwprintw(stdscr, n+1, xMax/3, "%3d  %-10s %-15s\t%s", n, p->name, p->tel, p->memo);

        p = p->next;
        n++;
    }
    refresh();
    getch();
    werase(stdscr);
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

void helpPrint(int xMax) {
    FILE *fp =  fopen(help, "r");
    char buf[MAX];
    int i = 0;
    while (fgets(buf, MAX, fp) != NULL)
        mvprintw(i++, xMax / 3, "%s", buf);
    fclose(fp);
    getch();
    werase(stdscr);
}

int main(void) {
    setlocale(LC_CTYPE, "ko_KR.utf8");

    struct Tel *head = NULL;
    head = init(head);

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);


    int x = 15, y = 20;
    WINDOW *menuwin = newwin(x, y, 0, xMax/2-10);
    keypad(menuwin, true);

    start_color();
    short COLOR_GRAY = 0;
    init_color(COLOR_GRAY, 200, 200, 200);
    init_pair(1, COLOR_WHITE, COLOR_GRAY);
    attron(COLOR_PAIR(1));

    int choice, highlight = 0, max = sizeof(menu)/ sizeof(menu[0]);

    while (1){
        mvwprintw(menuwin, 1, 1, "전화번호부");
        box(menuwin, 0, 0);
        for (int i = 0; i < max; ++i) {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, 3 + i, 1, menu[i]);
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_UP:
                if (highlight == 0)
                    break;
                highlight--;
                break;
            case KEY_DOWN:
                if (highlight == max-1)
                    break;
                highlight++;
                break;
            default:
                break;
        }
        if (choice == 10){
//            mvprintw(0, 0, "\n");
            if (highlight == max-1)
                break;
            switch (highlight) {
                case 0:
                    werase(menuwin);
                    wrefresh(menuwin);
                    helpPrint(xMax);
                    break;
                case 1:
                    werase(menuwin);
                    wrefresh(menuwin);
                    printAll(head, xMax);
                    break;
                case 2:
                    werase(menuwin);

                    werase(stdscr);
                    break;
                case 3:
                    mvprintw(0, 0, "%s", menu[highlight]);
                    break;
                case 4:
                    mvprintw(0, 0, "%s", menu[highlight]);
                    break;
                default:
                    break;
            }
            refresh();
        }

    }
    endwin();
    allFree(head);
    return 0;
}