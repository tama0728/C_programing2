#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <locale.h>

#define ESCAPE 27
#define ENTER 10

char *seq_item[] = {"",
                    "SUB_메뉴1",
                    "SUB_메뉴2",
                    "SUB_메뉴3",
                    "SUB_메뉴4",
                    "SUB_메뉴5"};
char *tr_item[] = {"",
                   "SUB_메뉴1",
                   "SUB_메뉴2",
                   "SUB_메뉴3",
                   "SUB_메뉴4"};
char *proc_item[] = {"",
                     "SUB_메뉴1",
                     "SUB_메뉴2",
                     "SUB_메뉴3",
                     "SUB_메뉴4"};

char *mng_item[] = {"",
                    "SUB_메뉴1",
                    "SUB_메뉴2",
                    "SUB_메뉴3",
                    "quit"};

/* title, status will be globall refresh */
WINDOW *titlebar, *statusbar;
WINDOW  *menubar;
WINDOW *dataview;

extern void refresh_status(char*);
extern void Init_Mana(int, char**);
extern void view_tr(WINDOW *, int , int);
extern void view_proc(WINDOW *, int);
extern void view_seq(WINDOW *, int);

void init_screen()
{
    initscr();
    start_color();
    noecho();
    keypad(stdscr, TRUE);
}

void end_screen()
{
    delwin(titlebar);
    delwin(statusbar);
    delwin(dataview);
    delwin(menubar);
    endwin();

    exit(0);
}

static void end_proc(int p_signo)
{
    char        _Log_Buf [BUFSIZ];

    strcat(_Log_Buf, " 프로세스를 종료합니다.");
    refresh_status(_Log_Buf);
    end_screen();
}

static void        Setsigfatal(void)
{
    signal (SIGINT,     end_proc);
    signal (SIGKILL,    end_proc);
    signal (SIGQUIT,    end_proc);
    signal (SIGILL,     end_proc);
    signal (SIGTERM,    end_proc);
    signal (SIGBUS,     end_proc);
    signal (SIGSEGV,    end_proc);
    signal (SIGHUP,     end_proc);

    return;
}

void refresh_title()
{
    time_t tloc;
    struct tm *tp;
    char date_time[60];

    time(&tloc);
    tp = localtime(&tloc);

    strftime(date_time, 22, "%Y/%m/%d  %H:%M:%S", tp);

    wmove(titlebar, 0, 2);
    waddstr(titlebar, "메뉴 테스트 시스템");
    wmove(titlebar, 0, 60);
    waddstr(titlebar, date_time);
    wrefresh(titlebar);
}

void refresh_status(char *msg)
{
    char blank[80];

    memset(blank, 0x20, sizeof(blank));

    wbkgd(statusbar, A_REVERSE);
    wmove(statusbar, 0, 1);
    wprintw(statusbar,"☞ ");
    wmove(statusbar, 0, 4);
    wprintw(statusbar, blank);
    wmove(statusbar, 0, 4);
    wprintw(statusbar, msg);
    wrefresh(statusbar);
}

void make_menubar(WINDOW *menubar)
{
    box(menubar, 0,0);
    wbkgd(menubar, A_REVERSE);

    wmove(menubar, 1, 5);
    wattron(menubar, A_REVERSE);
    waddstr(menubar, "메뉴1");
    waddstr(menubar, "(s)");

    wmove(menubar, 1, 25);
    wattron(menubar, A_REVERSE);
    waddstr(menubar, "메뉴2");
    waddstr(menubar, "(t)");

    wmove(menubar, 1, 45);
    wattron(menubar, A_REVERSE);
    waddstr(menubar, "메뉴3");
    waddstr(menubar, "(p)");

    wmove(menubar, 1, 65);
    wattron(menubar, A_REVERSE);
    waddstr(menubar, "메뉴4");
    waddstr(menubar, "(m)");

}

void menu_list(WINDOW **items, char **menu, int cnt, int start_col)
{
    int i;

    items[0]= newwin(cnt+1,19, 3,start_col);
    box(items[0], ACS_VLINE, ACS_HLINE);

    for (i =1; i < cnt; i++)
        items[i]=subwin(items[0], 1, 17, i+3, start_col+1);

    for (i =1; i < cnt; i++)
        wprintw((WINDOW *)items[i], "%s",menu[i]);

    wbkgd(items[1], A_UNDERLINE|A_STANDOUT);
    wrefresh(items[0]);

    return;
}

int scroll_menu(WINDOW **items,int count,int menu_start_col, int index_num)
{
    int key;
    int selected=1, before = 1;

    while (1)
    {
        halfdelay(100);
        switch((key=getch())) {
            case KEY_DOWN:
                selected=(selected+1) % count;
                if (selected == 0)
                    selected = 1;
                break;
            case KEY_UP:
                selected=(selected+count-1) % count;
                if (selected == 0)
                    selected = count - 1;
                break;
            case KEY_LEFT:
                return key;
            case KEY_RIGHT:
                return key;
            case ESCAPE:
                return -1;
            case ENTER:
                return selected;
            default:
                return -1;
        }

        if (selected != before)
        {
            wbkgd(items[before], COLOR_PAIR(0));
            wnoutrefresh(items[before]);
            before = selected;
        }
        wbkgd(items[selected],A_REVERSE);
        wnoutrefresh(items[selected]);
        doupdate();
    }
}

void delete_menu(WINDOW **items, int count)
{
    int i;

    for (i = 0; i < count; i++)
        delwin((WINDOW *)items[i]);
}

int check_quit()
{
    WINDOW *check;
    int key;

    check = newwin(3, 30, 10, 15);
    wmove(check, 1, 4);
    wprintw(check, " Exit program (y/n) ? ");
    box(check, ACS_VLINE, ACS_HLINE);
    refresh();
    key = wgetch(check);
    delwin(check);
    if (key == 'y')
        return 1;
    else
        return 0;
}

/* 사용자가 선택할 수 있는 메뉴의 갯수는 10개보다 작다는 가정하에 작업.
 * key 입력값은 항상 '0'보다 큰 값들이 발생한다고 가정.
 */
int move_menu(int presel, int key, WINDOW **menu_items)
{
    int sitem = key;
    int before_pos = '0';

    while (sitem > '0') {
        switch(sitem) {
            case KEY_RIGHT:
                if (before_pos < '4' && before_pos >= '1')
                    sitem = before_pos + 1;
                else if (before_pos == '4')
                    sitem = '1';
                else
                    sitem = 0;
                break;
            case KEY_LEFT :
                if (before_pos > '1' && before_pos <= '4')
                    sitem = before_pos - 1;
                else if (before_pos == '1')
                    sitem = '4';
                else
                    sitem = 0;

                break;
            case '1':
            case 's':
                before_pos = '1';
                menu_list(menu_items, seq_item, 6, 5);
                sitem = scroll_menu(menu_items, 6, 5, 0);
                delete_menu(menu_items, 6);

                if(sitem < 10 && sitem >= 0)
                    return 100+sitem;
                break;
            case '2':
            case 't':
                before_pos = '2';
                menu_list(menu_items, tr_item, 5, 25);
                sitem = scroll_menu(menu_items, 5, 20, 0);
                delete_menu(menu_items, 5);

                if(sitem < 10 && sitem >= 0)
                    return 200+sitem;
                break;
            case '3':
            case 'p':
                before_pos = '3';
                menu_list(menu_items, proc_item, 5, 45);
                sitem = scroll_menu(menu_items, 5, 40, 0);
                delete_menu(menu_items, 5);

                if(sitem < 10 && sitem >= 0)
                    return 300+sitem;
                break;
            case '4':
            case 'm':
                before_pos = '4';
                menu_list(menu_items, mng_item, 5, 60);
                sitem = scroll_menu(menu_items, 5, 60, 0);
                delete_menu(menu_items, 5);

                if (sitem == 2)
                {
                    sitem = 'q';
                    break;
                }
                if(sitem < 10 && sitem >= 0)
                    return 400+sitem;
                break;
            case 'q':
                if( check_quit() )
                    end_screen();
            default:
                //usleep(100);
                return presel;
        }
        touchwin(stdscr);
        refresh_title();
        refresh();
    }
    return presel;
}

int main(int argc, char **argv)
{
    setlocale(LC_CTYPE, "ko_KR.utf8");
    WINDOW *menu_items[10];
    int key;
    int row, col;
    int sel;

    Setsigfatal ();
    init_screen();

    titlebar = subwin(stdscr, 1, 80, 0, 0);
    menubar = subwin(stdscr, 3, 80, 1, 0);
    dataview = subwin(stdscr, 36, 80, 4, 0);
    statusbar = subwin(stdscr, 1, 79, 40, 1);

    getmaxyx(stdscr,row,col);
    if (row < 40 || col < 80)
    {
        refresh_status("터미널의 사이즈가 너무 작습니다");
        end_screen();
        return 0;
    }

    refresh_title();
    make_menubar(menubar);
    refresh_status("메뉴를 선택하세요");
    refresh();

    while(1)
    {
        halfdelay(100);
        key = getch();

        if ( ( key == 'q' || key == ESCAPE )
             && check_quit() )
            break;

        if ( key != KEY_UP
             && key != KEY_DOWN
             && key != ERR)
            sel = move_menu(sel, key, menu_items);

        switch((int)sel/100) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                refresh_status("메뉴를 선택하세요");
                break;
        }

        touchwin(stdscr);
        refresh_title();
        refresh();
    }

    end_screen();
    return 0;
}