#ifndef COLUMNGRABBER_H
#define COLUMNGRABBER_H

#include <stdio.h>
#include <stdbool.h>
#include "mission.h"
#include "checker.h"


// Function that grabs numbers from an array in a "column"
// Takes in a void pointer that has an int ID and an array of ints, and array of chars
void* columnGrabber(void* ptr) {

    struct Mission* a1 = (struct Mission*) ptr;     // Cast void ptr into mission ptr
    int colVals[9];       // Setup an array of ints
    int colIndex = a1->id;   // Grab the column number

    // Go through the Mission->array
    for (int i = 0; i < 9; i++) {

        //Grab the proper value from the Mission->array and store it in colVals
        colVals[i] = a1->array[i * 9 + colIndex];
    }

    // Pass the column values to the checker function, report results
    a1->success = checker(colVals);
}

#endif //COLUMNGRABBER_H

// Example output should be formatted as such:
// Row 4 doesn't have the required values.
// Column 3 doesn't have the required values.
// The middle left subgrid doesn't have the required values.
// The input is not a valid Sudoku.