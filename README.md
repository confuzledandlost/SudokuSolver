# sudoku-project

Starter code for the sudoku project.

    $ make sudoku.x
    gcc -o sudoku.x -g -lpthread sudoku.c
    $ ./sudoku.x < someInputFile

#include <stdio.h>


bool rowGrabber(*Mission a1) {
    int rowVals[9];
    rowIndex = a1.id * 9;

    for(int i = 0; i < 9; i++) {
        rowVals[i] = a1.array[rowIndex];
        rowIndex++;
    }
    if(checker(rowVals)) {
        return true;
    } else {
        printf("Row %d doesn't have the required values \n", a1.id);
        return false;
    }
}
