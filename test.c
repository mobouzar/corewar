#include <ncurses.h>

int main(int argc, char *argv[])
{
    initscr();
    WINDOW * win = newwin(8,15,1,1);
    box(win,0,0);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(1));
    mvwprintw(win,1,1,"colored text");
    wrefresh(win);
    getch();
    return 0;
}