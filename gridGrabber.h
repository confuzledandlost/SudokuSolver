#ifndef GRIDGRABBER_H
#define GRIDGRABBER_H

#include <stdio.h>
#include <stdbool.h>
#include "mission.h"
#include "checker.h"

// Function that grabs numbers from an array in a 3x3 subgrid
// Takes in a void pointer that has an int ID, an array of ints, and array of chars
void* gridGrabber(void* ptr) {

    struct Mission* a1 = (struct Mission*) ptr;   // Cast void ptr into mission ptr
    int gridVals[9];   // Array to store the 3x3 subgrid values
    int startRow = (a1->id / 3) * 3;   // Determine the starting row of the subgrid
    int startCol = (a1->id % 3) * 3;   // Determine the starting column of the subgrid
    int index = 0;   // Index for filling gridVals

    // Extract values from the 3x3 subgrid
    for (int i = 0; i < 3; i++) {  // Rows within the subgrid
        for (int j = 0; j < 3; j++) {  // Columns within the subgrid
            gridVals[index++] = a1->array[(startRow + i) * 9 + (startCol + j)];
        }
    }

    // Pass the 3x3 subgrid values to the checker function, report results
    a1->success = checker(gridVals);
}

#endif //GRIDGRABBER_H

// Example output should be formatted as such:
// Row 4 doesn't have the required values.
// Column 3 doesn't have the required values.
// The middle left subgrid doesn't have the required values.
// The input is not a valid Sudoku.