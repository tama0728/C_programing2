//
// Created by 김동윤 on 2023/06/02.
//

#include <ncurses.h>

int main(void) {
    initscr();
    printw("Hello World !!!");
    refresh();
    getch();
    endwin();
    return 0;
}
