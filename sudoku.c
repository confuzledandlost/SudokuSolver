#include <stdio.h>  
#include <unistd.h> 
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/wait.h>

struct Mission {
  int id;
  int* array;
  int success;
};

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

// Function that grabs numbers from an array in a "row"
// Takes in a void pointer that has an int ID and an array of ints, and array of chars, and a message
void* rowGrabber(void* ptr) {

  //cast the pointer so we can access the mission data
  struct Mission* a1 = (struct Mission*) ptr;
  int rowVals[9];
  int rowIndex = a1->id * 9;

  for(int i = 0; i < 9; i++) {
    rowVals[i] = a1->array[rowIndex];
    rowIndex++;
  }

  // Pass the row values to the checker function, report results
  a1->success = checker(rowVals);
}

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

int main(int argc, char *argv[]) {
  // Array mapping subgrid IDs to their corresponding names
  const char* subgridNames[] = {
    "top left", "top middle", "top right",
    "middle left", "middle middle", "middle right",
    "bottom left", "bottom middle", "bottom right"
  };

  parse_args(argc, argv);

  if (verbose && use_fork) {
      printf("We are forking child processes as workers.\n");
  } else if (verbose) {
      printf("We are using worker threads.\n");
  }


  //make an array for the solution
  #define BOARDSIZE 81
  int solution[BOARDSIZE];

  //read all the input
  for (int i = 0; i < BOARDSIZE; i = i + 1) {
    scanf("%d", &solution[i]);

    // printf("%d ", solution[i]);
    // if ((i + 1) % 27 == 0)
    //   printf("\n");
    // if ((i+1) % 9 == 0)
    //   printf("\n");
    // else if ((i+1) % 3 == 0)
    //   printf(" ");
  }

  //nine rows, columns, grids.
  #define WORKERCOUNT 27

  //threads or pids to track our workers
  pthread_t thread[WORKERCOUNT];
  pid_t p[WORKERCOUNT];

  //create space to define all our tasks
  struct Mission mission[WORKERCOUNT];

  //rows
  for (int i = 0; i < 9; i = i + 1) {
    mission[i].array = solution;    //point to the input
    mission[i].id = i;              //0-8 id for the value grabbing algorithm
    mission[i].success = false;     //whether the values are acceptable
    if (use_fork) {
      p[i] = fork();
      if (p[i] == 0) {
        rowGrabber((void*) &mission[i]);
        exit(mission[i].success);
      }
    }
    else {
      pthread_create(&thread[i], NULL, *rowGrabber, (void*) &mission[i]);
    }
  }

  //columns
  for (int i = 0; i < 9; i = i + 1) {
    mission[i+9].array = solution;
    mission[i+9].id = i;
    mission[i+9].success = false;
    if (use_fork) {
    p[i+9] = fork();
    if (p[i+9] == 0) {
      columnGrabber((void*) &mission[i+9]);
      exit(mission[i+9].success);
    }
    }
    else {
      pthread_create(&thread[i+9], NULL, *columnGrabber, (void*) &mission[i+9]);
    }
  }

  //grids
  for (int i = 0; i < 9; i = i + 1) {
    mission[i+18].array = solution;
    mission[i+18].id = i;
    mission[i+18].success = false;
    if (use_fork) {
    p[i+18] = fork();
    if (p[i+18] == 0) {
      gridGrabber((void*) &mission[i+18]);
      exit(mission[i+18].success);
    }
    }
    else {
      pthread_create(&thread[i+18], NULL, *gridGrabber, (void*) &mission[i+18]);
    }
   }

  //collect answers
  int valid = 1;
  for (int i = 0; i < WORKERCOUNT; i = i + 1) {
    //see if this test passed or not
    int success;

    if (use_fork) {
      int status;
      waitpid(p[i], &status, (long) NULL);

      if (!WIFEXITED(status)) {
        printf("One or more threads errored out.\n");
        exit(-1);
      }

      success = WEXITSTATUS(status);
    }
    else {
      pthread_join(thread[i], NULL);
      
      success = mission[i].success;
    }

    //complain about failures
    if (!success) {
      if (i < 9)
        printf("Row %d doesn't have the required values.\n", i + 1);
      else if (i < 18) {
        printf("Column %d doesn't have the required values.\n", i % 9 + 1);
      }
      else {
        printf("The %s subgrid doesn't have the required values.\n", subgridNames[i % 9]);
      }
    }
    
    //track overall success
    valid &= success;
  }

  //tell the user whether they're an idiot
  if (valid) {
    printf("The input is a valid Sudoku.\n");
  } else{
      printf("The input is not a valid Sudoku.\n");
  }

  return 0;
}