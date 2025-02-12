#include <stdio.h>  
#include <unistd.h> 
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

/* These are the only two global variables allowed in your program */
static int verbose = 0;
static int use_fork = 0;


// This is a simple function to parse the --fork argument.
// It also supports --verbose, -v
void parse_args(int argc, char *argv[])
{
    int c;
    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose", no_argument,       0, 'v'},
            {"fork",    no_argument,       0, 'f'},
            {0, 0, 0, 0}
        };
        int option_index = 0;
        c = getopt_long (argc, argv, "vf", long_options, &option_index);
        if (c == -1) break;

        switch (c)
        {
            case 'f':
                use_fork = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                exit(1);
        }
    }
}


int main(int argc, char *argv[])
{
    parse_args(argc, argv);

    if (verbose && use_fork) {
        printf("We are forking child processes as workers.\n");
    } else if (verbose) {
        printf("We are using worker threads.\n");
    }


    return 0;
}


// Function that checks if array of numbers has only the 1-9, no repeats, no missing numbers, in any order
// Takes in an array of ints, returns a boolean
bool checker(int* nums[]) {

	// Setup an array of booleans
	bool* exists[9] = false;

	// Loop through input array and check against exists array
	for (int i = 0; i < 9; i++) {

		// Hold the current number for safe-keeping (and add 1)
		int curr = nums[i] + 1;

		// Check if number is in bounds
		if ((curr < 1) || (curr > 9)) {

			// Return false if it isn't
			return false;

		}
		
		// Compare number against exists array
		if (exists[curr] == false) {

			// Flip boolean to true if it's false
			exists[curr] == true;
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
