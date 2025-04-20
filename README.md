# Sudoku Solver Project

This project validates whether a given Sudoku solution is correct. It uses multithreading or multiprocessing to parallelize the validation of rows, columns, and subgrids.

## Compilation

To compile the program, use the provided `Makefile`:

```sh
$ make sudoku.x
```
This will generate an executable named sudoku.x.

## Usage

Run the program by providing a Sudoku solution as input:
```sh
$ [sudoku.x](http://_vscodecontentref_/3) < someInputFile
```

## Command-Line Options

--verbose or -v: Enables verbose output.
--fork or -f: Uses child processes instead of threads for parallelism.

## Code Overview
### Key Data Structures

struct Mission: Used to pass information to worker threads or processes.
int id: Identifies the row, column, or subgrid to validate.
int* array: Pointer to the Sudoku solution array.
int success: Indicates whether the validation succeeded (1 for success, 0 for failure).

## Functions

bool checker(int nums[])
Validates that an array contains all digits from 1 to 9 without duplicates.

void* rowGrabber(void* ptr)
Extracts a row from the Sudoku solution and validates it using checker.

void* columnGrabber(void* ptr)
Extracts a column from the Sudoku solution and validates it using checker.

void* gridGrabber(void* ptr)
Extracts a 3x3 subgrid from the Sudoku solution and validates it using checker.

void parse_args(int argc, char *argv[])
Parses command-line arguments to set global flags for verbosity and multiprocessing.

## Program Flow

**Input Reading:** 

Reads a 9x9 Sudoku solution into an array.

**Worker Initialization:**

Creates 27 workers (9 for rows, 9 for columns, 9 for subgrids).
Each worker validates a specific row, column, or subgrid.
Workers use either threads or child processes based on the --fork flag.

**Validation:**

Each worker reports success or failure.
The main thread collects results and prints detailed error messages for invalid rows, columns, or subgrids.

**Output:**

Prints whether the input is a valid Sudoku solution.

Example Output
For an invalid Sudoku solution:

```
Row 4 doesn't have the required values.
Column 3 doesn't have the required values.
The middle left subgrid doesn't have the required values.
The input is not a valid Sudoku.
```

For a valid Sudoku solution:

```
The input is a valid Sudoku.
```

## Notes
The program ensures no resource leaks by properly joining threads or waiting for child processes.
Only two global variables (verbose and use_fork) are used, as required.
