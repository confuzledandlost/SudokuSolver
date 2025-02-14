#ifndef COLUMNGRABBER_H
#define COLUMNGRABBER_H

#include <stdio.h>
#include <stdbool.h>
#include "mission.h"
#include "checker.h"


// Function that grabs numbers from an array in a "column"
// Takes in a Mission struct pointer that has an int ID and an array of ints, returns a boolean
bool columnGrabber(struct Mission* a1) {

    // Setup an array of ints and grab the column number
    int colVals[9];
    int colIndex = a1->id;

    // Go through the Mission->array
    for (int i = 0; i < 9; i++) {

        //Grab the proper value from the Mission->array and store it in colVals
        colVals[i] = a1->array[i * 9 + colIndex];
    }

    // Pass the column values to the checker function
    if(checker(colVals)) {
        return true;    // If it checks out, return true
    } else {
        printf("Column %d doesn't have the required values \n", a1->id);
        return false;    // If not, return false
    }
}

#endif //COLUMNGRABBER_H
