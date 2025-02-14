#ifndef GRIDGRABBER_H
#define GRIDGRABBER_H

#include <stdio.h>
#include <stdbool.h>
#include "mission.h"
#include "checker.h"

// Function that grabs numbers from an array in a 3x3 subgrid
// Takes in a Mission struct pointer that has an int ID and an array of ints, returns a boolean
bool gridGrabber(struct Mission* a1) {

    int gridVals[9];   // Array to store the 3x3 subgrid values
    int startRow = (a1->id / 3) * 3;   // Determine the starting row of the subgrid
    int startCol = (a1->id % 3) * 3;   // Determine the starting column of the subgrid
    int index = 0;   // Index for filling gridVals

    // Array mapping subgrid IDs to their corresponding names
    const char* subgridNames[] = {
        "top left", "top middle", "top right",
        "middle left", "middle middle", "middle right",
        "bottom left", "bottom middle", "bottom right"
    };

    // Extract values from the 3x3 subgrid
    for (int i = 0; i < 3; i++) {  // Rows within the subgrid
        for (int j = 0; j < 3; j++) {  // Columns within the subgrid
            gridVals[index++] = a1->array[(startRow + i) * 9 + (startCol + j)];
        }
    }

    // Pass the 3x3 subgrid values to the checker function
    if (checker(gridVals)) {
        return true;    // If it checks out, return true
    } else {
        printf("The %s subgrid doesn't have the required values.\n", subgridNames[a1->id]);
        return false;    // If not, return false
    }
}


#endif //GRIDGRABBER_H
