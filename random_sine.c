#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main() {
    initscr(); // initalize screen
    start_color(); // enable colors
    noecho(); // disable seeing typed characters
    curs_set(0); // disable cursor
    nodelay(stdscr, TRUE); // disable delay when using getch()

    long seconds;
    struct timespec time_s;

    // colors
    init_pair(1, COLOR_RED, COLOR_RED); 
    init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA); 
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_BLUE, COLOR_BLUE); 
    init_pair(6, COLOR_GREEN, COLOR_GREEN);

    int ch;
    int x, y;
    double sin_val = 0;
    while (ch != 'Q') {
        clock_gettime(CLOCK_REALTIME, &time_s);
        seconds = time_s.tv_nsec;
        ch = getch(); // get user input
        // nested for loop to 'build' pixels 
        for (int y = 0; y < getmaxy(stdscr); y++) { // for each row...
            
            sin_val = (double) seconds;
            for (int x = 0; x < getmaxx(stdscr); x++) { // for each column in the row
                sin_val = sin((sin_val + (y + x)) + seconds);
                if (sin_val >= 0.0 && sin_val < 0.5) {
                    attron(COLOR_PAIR(1));
                    //sin_val = rand() % getmaxx(stdscr);
                    sin_val = sin((sin_val + (y - x)) + seconds);
                    mvprintw(y, x, "-");
                }
                else if (sin_val >= 0.5) {
                    attron(COLOR_PAIR(2));
                    mvprintw(y, x, ".");
                }
                else if (sin_val < 0.0 && sin_val >= -0.5){
                    attron(COLOR_PAIR(3));
                    sin_val = sin((sin_val + (x - y)) + seconds);
                    mvprintw(y, x, "'");
                }
                else if (sin_val < -0.5 && sin_val > -1.0){
                    attron(COLOR_PAIR(4));
                    sin_val = sin((sin_val + (y + x)) - seconds);
                    mvprintw(y, x, ",");
                }
                //mvprintw(y, x, " ");
                attrset(A_NORMAL);
                //sin_val = rand() % getmaxx(stdscr);
            }
        }
        napms(150); // set 'framerate'
        
        //mvprintw(0, 0, "%lf", sin_val);
    }
    endwin();
    return 0;


}