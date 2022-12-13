// dec 12th 22

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    initscr(); // initalize console
    start_color(); // allow colors
    noecho(); // disable seeing typed chars in console
    curs_set(0); // disable cursor
    keypad(stdscr, TRUE); // allow KEY_UP, KEY_DOWN, etc.
    cbreak();
    //scrollok(stdscr, FALSE);
    nodelay(stdscr, TRUE); // disable delay for getch

    // colors for text
    init_pair(1, COLOR_RED, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); 
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK); 
    init_pair(6, COLOR_GREEN, COLOR_BLACK);



    char msg[] = "hello, world";

    int ch;
    int x, y = 0;
    int speed = 50;
    while (ch != 'Q') {
        ch = getch();
        mvprintw(0, 0, "(%d, %d)\nspeed: %d ms", x, y, speed);
        
        y = getmaxy(stdscr) / 2;

        if (ch == KEY_UP) {
            if (speed >= 100) {
                speed = 100;
            }
            speed++;
        }
        else if (ch == KEY_DOWN) {
            if (speed <= 1) {
                speed = 1;
            }
            speed--;
        }

        if (x > (getmaxx(stdscr) - strlen(msg)) || x < 0) {
            x = 0;
        }

        attron(COLOR_PAIR((rand() % 6) + 1)); // set random color
        mvprintw(y, x, "%s", msg); // print string at cur. position
        attrset(A_NORMAL); // reset colors
        x++; // increment x pos by 1
        refresh(); // refresh screen now and display what we have

        erase(); // after displaying, erase everything currently on the screen
        napms(speed); // wait some amount of ms before updating screen
        refresh(); // refresh screen
        
    }

    endwin();
    return 0;
}