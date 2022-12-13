// dec 11th 22

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main() {

    initscr(); // initalize curses
    start_color(); // enable colors in terminal
    // init colors we are going to use: at this point its just a rainbow
    init_pair(1, COLOR_RED, COLOR_BLACK); 
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); 
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK); 
    init_pair(6, COLOR_GREEN, COLOR_BLACK);

    noecho(); // disable seeing typed characters

    char title_msg[] = "random_text.c";
    char welcome_msg[] = "'Q' to quit, 'C' to clear screen";

    attron(A_BOLD); // bold the title
    mvprintw((getmaxy(stdscr) / 2), (getmaxx(stdscr) / 2) - strlen(title_msg) / 2, "%s", title_msg);
    attroff(A_BOLD);
    mvprintw((getmaxy(stdscr) / 2) + 2, (getmaxx(stdscr) / 2) - strlen(welcome_msg) / 2, "%s", welcome_msg); // print welcome screen in middle of console

    getch(); // display welcome screen first, then once user presses a button we continue
    erase(); // clear the screen

    int ch, rand_attr;
    while (ch != 'Q') { // while loop runs as long as the user doesnt press "Q"
        
        ch = getch(); // get char from user input

        if (ch == 'C')
            erase(); // clear screen if we press 'C'

        attron(COLOR_PAIR((rand() % 6) + 1)); // randomly assign colors to text

        switch (rand() % 2) { // switch (used to hold more) that either displays bold or resets to white
            case 0:
                attron(A_BOLD); // bold
                break;
            case 1:
                attrset(A_NORMAL); // reset attributes (also white)
                break;
        }

        mvprintw(rand() % getmaxy(stdscr), rand() % getmaxx(stdscr), "%c", ch); // display typed char to console screen
        
        refresh(); // refresh entire screen

    }

    endwin(); // if we exit the loop, then end the program
    return 0;

}