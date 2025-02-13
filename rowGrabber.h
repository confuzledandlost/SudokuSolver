//
// Created by Sean Belingheri on 2/13/25.
//

#ifndef SUDOKUSOLVER_ROWGRABBER_H
#define SUDOKUSOLVER_ROWGRABBER_H

#include <stdio.h>
#include <stdbool.h>
#include "mission.h"
#include "checker.h"

bool rowGrabber(struct Mission* a1) {
    int rowVals[9];
    int rowIndex = a1->id * 9;

    for(int i = 0; i < 9; i++) {
        rowVals[i] = a1->array[rowIndex];
        rowIndex++;
    }
    if(checker(rowVals)) {
        return true;
    } else {
        printf("Row %d doesn't have the required values \n", a1->id);
        return false;
    }
}

#endif //SUDOKUSOLVER_ROWGRABBER_H
