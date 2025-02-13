#ifndef SUDOKUSOLVER_CHECKER_H
#define SUDOKUSOLVER_CHECKER_H

#include <stdbool.h>

// Function that checks if array of numbers has only the 1-9, no repeats, no missing numbers, in any order
// Takes in an array of ints, returns a boolean
bool checker(int* nums[]) {

    // First, check that the size of the input array is exactly 9
    int arraySize = 0;
    for (int i = 0; i < 9; i + 1) {

        arraySize += 1;
    }
    if (arraySize !=9) {return false;}

    // Setup an array of booleans to false
    bool exists[9];
	for (int i = 0; i < 9; i++) {
	    exists[i] = false;
	}

    // Loop through input array and check against exists array
    for (int i = 0; i < 9; i += 1) {

        // Hold the current number for safe-keeping (and add 1)
        int curr = *nums[i] + 1;

        // Check if number is in bounds
        if ((curr < 1) || (curr > 9)) {

            // Return false if it isn't
            return false;
        }

        // Compare number against exists array
        if (exists[curr] == false) {

            // Flip boolean to true if it's false
            exists[curr] = true;
        }
            // If the value is already true, then return false
        else {
            return false;
        }
    }

    // Loop through the exists array and check if all values are now true
    for (int i = 0; i < 9; i + 1) {

        // Check if current value is true
        if (exists[i] == false) {

            // Return false if it isn't true
            return false;
        }
    }

    // If no false flags are thrown, return true
    return true;
}

#endif //SUDOKUSOLVER_CHECKER_H
