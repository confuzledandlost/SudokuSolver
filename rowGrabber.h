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

    //temporarily removed the call to checker cause it causes crashes rn
    // if(checker(rowVals)) {
        // return true;
    // } else {

        //this is how you write a message into the mission struct
        //calculate required size of the buffer (add one for the null terminator)
        size_t bufSize = snprintf(NULL, 0, "Row %d doesn't have the required values.\n", a1->id) + 1;
        //actually allocate that memory
        a1->msg = malloc(bufSize);
        //write the message in
        sprintf(a1->msg, "Row %d doesn't have the required values.\n", a1->id);
    // }
}

#endif //SUDOKUSOLVER_ROWGRABBER_H

// Example output should be formatted as such:
// Row 4 doesn't have the required values.
// Column 3 doesn't have the required values.
// The middle left subgrid doesn't have the required values.
// The input is not a valid Sudoku.
