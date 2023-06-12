//
// Created by 김동윤 on 2023/06/02.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <locale.h>

#define MAX 1024
#define data "./data.txt"
#define help "./help.txt"

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
//help.txt 출력
void helpPrint() {
    FILE *fp =  fopen(help, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    int x, y;
    getmaxyx(stdscr, y, x);
    char buf[MAX];
    int i = 0;
    while (fgets(buf, MAX, fp) != NULL)
        mvprintw(i++, 0, "%s", buf);
    fclose(fp);
    getch();
    werase(stdscr);
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
void printAll(Tel *head) {
    Tel *p = head;
    int n = 1, j, max = 0;
    mvwprintw(stdscr, 0, 0, "%3s  |%-10s |%-15s    |%s", "No", "Name", "Tel", "Memo");
    //리스트의 끝까지 이동하면서 출력
    while (p != NULL) {
        mvwprintw(stdscr, n, 0, "%3d  |%-10s |%-15s    |%s", n, p->name, p->tel, p->memo);

        p = p->next;
        n++;
    }
    refresh();
    printw("\n\npress any key to continue.");
    getch();
    werase(stdscr);
}

//key 값을 받아 해당 노드 찾기
void searchTel(struct Tel *head){
    char key[40] = {0};
    printw("please enter key: ");
    getstr(key);
    if (strlen(key) == 0) {
        wprintw(stdscr, "\nNo key entered.\n\npress any key to continue.");
        getch();
        werase(stdscr);
        return;
    }
    struct Tel *p = head;
    int n = 1;
    while (p != NULL) {
        //name, tel, memo에 key 값이 포함되어 있으면 출력
        if (strstr(p->name, key) != NULL || strstr(p->tel, key) != NULL || strstr(p->memo, key) != NULL) {
            mvprintw(n, 0,"%3d  |%-10s |%-15s    |%s",n, p->name, p->tel, p->memo);
            n++;
        }
        p = p->next;
    }
    //key 값이 없으면 no match found 출력
    if (n == 1)
        mvprintw(n+1, 0, "\nno match found.\n\npress any key to continue.");
    else
        mvprintw(n+1, 0, "match found.\n\npress any key to continue.");
    refresh();
    getch();
}

Tel *add(Tel *head) {
    char name[30] = {0}, tel[20] = {0}, memo[40] = {0};
    printw("name: ");
    getstr(name);
    printw("tel: ");
    getstr(tel);
    printw("memo: ");
    getstr(memo);
    refresh();
    if (strlen(name) == 0 || strlen(tel) == 0) {
        printw("\nNo name or tel entered.\n\npress any key to continue.");
        getch();
        werase(stdscr);
        return head;
    }

    printw("\n%s %s %s\n\nadd?[Y/N] ", name, tel, memo);
    int c = getch();
    if (c != 'Y' && c != 'y') {
        printw("\n\nadd canceled.\n\npress any key to continue.");
        getch();
        return head;
    }
    head = insert(head, name, tel, memo);
    printw("\n\nadded.\n\npress any key to continue.");
    getch();
    werase(stdscr);
    return head;
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


//리스트에서 삭제
Tel *delete(struct Tel *head) {
    char key[40] = {0};
    printw("please enter key: ");
    getstr(key);

    if (strlen(key) == 0) {
        wprintw(stdscr, "\nNo key entered.\n\npress any key to continue.");
        getch();
        werase(stdscr);
        return head;
    }
    struct Tel *p = head;
    int n = 1, i = 0, tmep[MAX] = {0};
    //key 값이 포함된 노드 찾기
    while (p != NULL) {
        if (strstr(p->name, key) != NULL || strstr(p->tel, key) != NULL || strstr(p->memo, key) != NULL) {
            printw("%3d  |%-10s |%-15s    |%s\n", n, p->name, p->tel, p->memo);
            tmep[n-1] = i;      //key 값이 포함된 노드의 인덱스 저장
            n++;
        }
        i++;
        p = p->next;
    }
    //key 값이 없으면 no match found 출력
    if (n == 1) {
        printw("\nno match found.\n");
        refresh();
        printw("\n\npress any key to continue.");
        getch();
        return head;
    }
    printw("which one? ");
    refresh();
    char num[10];
    i = 0;
    scanw("%s", num);
    //입력이 숫자가 아니거나 1~n-1 사이의 숫자가 아니면 wrong input 출력
    do {
        if (!isdigit(num[i]) || num[i] == '\0') {
            printw("\nNot number.\n");
            printw("\ndelete canceled.\n\npress any key to continue.");
            getch();
            return head;
        }
        i++;
    } while (num[i] != '\0');

    int k = atoi(num);      //삭제할 노드의 인덱스
    if (k < 1 || k >= n) {
        printw("\nWrong input.\n");
        printw("\ndelete canceled.\n\npress any key to continue.");
        getch();
        return head;
    }
    k = tmep[k-1];
    p = head;
    //삭제할 노드까지 이동
    for (int j = 0; j < k; ++j)
        p = p->next;
    //삭제할 노드가 head 노드이면 head를 다음 노드로 변경
    if (p == head) {
        head = head->next;
        free(p);
    } else {
        //삭제할 노드의 이전 노드를 다음 노드로 변경
        struct Tel *q = head;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
        free(p);
    }
    printw("\ndeleted.\n\npress any key to continue.");
    getch();
    return head;
}

int main(void) {
    setlocale(LC_CTYPE, "ko_KR.utf-8");
    struct Tel *head = NULL;
    head = init(head);

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int x = 20, y = 10;
    WINDOW *menuwin = newwin(y, x, 0, 0);
    keypad(menuwin, true);

    start_color();
    short COLOR_GRAY = 0;
    init_color(COLOR_GRAY, 200, 200, 200);
    init_pair(1, COLOR_WHITE, COLOR_GRAY);
    attron(COLOR_PAIR(1));

    int choice, highlight = 0, max = sizeof(menu)/ sizeof(menu[0]);

    while (1){
        mvwprintw(menuwin, 1, 1, "telbook");
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
            case 'q':
                endwin();
                save(head);
                return 0;
            default:
                break;
        }
        if (choice == 10){
            if (highlight == max-1)
                break;
            werase(menuwin);
            wrefresh(menuwin);
            switch (highlight) {
                case 0:
                    helpPrint();
                    break;
                case 1:
                    printAll(head);
                    break;
                case 2:
                    curs_set(1);
                    echo();
                    searchTel(head);
                    werase(stdscr);
                    curs_set(0);
                    noecho();
                    break;
                case 3:
                    curs_set(1);
                    echo();
                    head = add(head);
                    werase(stdscr);
                    curs_set(0);
                    noecho();
                    break;
                case 4:
                    curs_set(1);
                    echo();
                    head = delete(head);
                    werase(stdscr);
                    curs_set(0);
                    noecho();
                    break;
                default:
                    break;
            }
            refresh();
        }

    }
    save(head);
    endwin();
    allFree(head);
    return 0;
}
