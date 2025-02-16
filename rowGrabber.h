//
// Created by Sean Belingheri on 2/13/25.
//

#ifndef SUDOKUSOLVER_ROWGRABBER_H
#define SUDOKUSOLVER_ROWGRABBER_H

#include <stdio.h>
#include <stdbool.h>
#include "mission.h"
#include "checker.h"

//has to be a void* function(void*)
void* rowGrabber(void* ptr) {

    //cast the pointer so we can access the mission data
    struct Mission* a1 = (struct Mission*) ptr;
    int rowVals[9];
    int rowIndex = a1->id * 9;

    for(int i = 0; i < 9; i++) {
        rowVals[i] = a1->array[rowIndex];
        rowIndex++;
    }

    // Pass the row values to the checker function, report results
    a1->success = checker(rowVals);
}

#endif //SUDOKUSOLVER_ROWGRABBER_H

// Example output should be formatted as such:
// Row 4 doesn't have the required values.
// Column 3 doesn't have the required values.
// The middle left subgrid doesn't have the required values.
// The input is not a valid Sudoku.