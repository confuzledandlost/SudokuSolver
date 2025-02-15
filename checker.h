#ifndef SUDOKUSOLVER_CHECKER_H
#define SUDOKUSOLVER_CHECKER_H

#include <stdbool.h>

// Function that checks if array of numbers has only the 1-9, no repeats, no missing numbers, in any order
// Takes in an array of ints, returns a boolean
bool checker(int nums[]) {

    // Setup an array of booleans to false
    bool exists[9] = {false};

    // Loop through input array and check against exists array
    for (int i = 0; i < 9; i++) {

        // Hold the current number for safe-keeping (and add 1)
        int curr = nums[i];

        // Check if number is in bounds
        if (curr < 1 || curr > 9) {

            // Return false if it isn't
            return false;
        }

        // Compare number against exists array
        if (exists[curr - 1] == false) {

            // Flip boolean to true if it's false
            exists[curr - 1] = true;
        }
            // If the value is already true, then return false
        else {
            return false;
        }
    }

    // Loop through the exists array and check if all values are now true
    for (int i = 0; i < 9; i++) {

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
