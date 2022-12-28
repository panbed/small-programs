#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_array(int *array, int size, char *arr_name);
void populate_array(int *array, int size, WINDOW *window);
int* remake_array(int *array, int *size, WINDOW *window);

int main() {
    
    initscr(); // initalize window
    noecho(); // disable echo
    nodelay(stdscr, true); // disable delay with getch()
    curs_set(0); // disable cursor
    
    //int nums[50]; // create array
    int *nums = (int *) malloc(sizeof(int) * (getmaxy(stdscr) - 5));
    int numSize = getmaxy(stdscr) - 5; // get size of array
    mvprintw(0, 0, "%d", numSize);
    populate_array(nums, numSize, stdscr); // populate initial array
    
    int min, minIndex, temp; // init vars
    
    int ch;
    while (ch != 'q') {
        ch = getch(); // get current key (barely work just ctrl + c lol)

        for (int i = 0; i < numSize; i++) {
            min = nums[i]; // reset min variable
            for (int j = i; j < numSize; j++) {
                if (nums[j] <= min) { // if we find a new min
                    min = nums[j]; 
                    minIndex = j; // set the minIndex
                }
            }

            temp = nums[i]; // save current index
            nums[i] = nums[minIndex]; // replace current index with the minimum
            nums[minIndex] = temp; // place saved index where the min was before

            for (int y = 0; y < numSize; y++) {
                for (int x = 0; x < nums[y]; x++) {
                    if (y == minIndex)
                        mvprintw(y + ((getmaxy(stdscr) - numSize) / 2), x + ((getmaxx(stdscr) - nums[y]) / 2), ">"); // highlight current minimum
                    else if (y == i)
                        mvprintw(y + ((getmaxy(stdscr) - numSize) / 2), x + ((getmaxx(stdscr) - nums[y]) / 2), "<"); // also highlight current row
                    else
                        mvprintw(y + ((getmaxy(stdscr) - numSize) / 2), x + ((getmaxx(stdscr) - nums[y]) / 2), "."); // everything else is just ""."
                }
            }
            refresh(); // refresh screen after printing
            napms(100); // wait a few ms
            erase(); // erase screen after refreshing (printing) so that the old stuff isnt persistent
        }

        napms(1000); // after finishing sort, wait a second
        nums = remake_array(nums, &numSize, stdscr);
        populate_array(nums, numSize, stdscr); // then recreate the array with new random numbers
        
        erase(); // and then erase everything
    }
    

    endwin(); // exit window
    free(nums); // free array in heap
    return 0;
}

// OLD: use ncurses now
void print_array(int *array, int size, char *arr_name) {
    for (int i = 0; i < size; i++) {
        printf("%s[%d]: %d\n", arr_name, i, array[i]);
    }
    printf("\n");
}

void populate_array(int *array, int size, WINDOW *window) {
    srand(time(0)); // set seed to current time
    for (int i = 0; i < size; i++) {
        array[i] = (rand() % (getmaxx(stdscr) - 20)) + 1; // randomly insert values into array to sort later
    }
}

int* remake_array(int *array, int *size, WINDOW *window) {
    if (*size == (getmaxx(stdscr) + 5)) { // if nothing happened...
        return array; // ...then just return the same array
    }
    else {
        int *newarray = (int *) malloc(sizeof(int) * (getmaxy(stdscr) - 5)); // should allocate new array with a size of (term size in y) - 5
        free(array); // free old array (is this how it works i forgot)
        *size = getmaxy(stdscr) - 5; // update the size to reflect new window size
        return newarray; // return the new array
    }
}