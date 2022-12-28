#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    initscr(); // initalize screen
    start_color(); // enable colors
    noecho(); // disable seeing typed characters
    curs_set(0); // disable cursor
    nodelay(stdscr, TRUE); // disable delay when using getch()

    // colors
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);

    int ch;
    int x, y;
    while (ch != 'Q') {
        ch = getch(); // get user input
        // nested for loop to 'build' pixels 
        for (int y = 0; y < getmaxy(stdscr); y++) { // for each row...
            for (int x = 0; x < getmaxx(stdscr); x++) { // for each column in the row
                if (((rand() % 2) + 1) == 1) { // gen. random number, and if its 1,
                    attron(COLOR_PAIR(1)); // then we set the pixel white
                }
                mvprintw(y, x, " "); // draw a "blank" pixel
                attrset(A_NORMAL); // reset attributes
            }
        }
        napms(50); // set sleep time
    }

    endwin(); // end ncurses
    return 0; // end program


}