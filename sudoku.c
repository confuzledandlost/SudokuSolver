#include <stdio.h>  
#include <unistd.h> 
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include "mission.h"
#include "checker.h"
#include "rowGrabber.h"
#include "columnGrabber.h"
#include "gridGrabber.h"
#include <stdbool.h>

/* These are the only two global variables allowed in your program */
static int verbose = 0;
static int use_fork = 0;

// Array mapping subgrid IDs to their corresponding names
const char* subgridNames[] = {
    "top left", "top middle", "top right",
    "middle left", "middle middle", "middle right",
    "bottom left", "bottom middle", "bottom right"
};

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


  //make an array for the solution
  #define BOARDSIZE 81
  int solution[BOARDSIZE];
  pthread_t thread[9+9+9]; //nine rows, columns, grids.
  pid_t p[9+9+9];

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

  //create a boat load of threads or forks
  struct Mission mission[9+9+9];

  //rows
  for (int i = 0; i < 9; i = i + 1) {
    mission[i].array = solution;
    mission[i].id = i;
    mission[i].success = false;
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

  //columns
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
  for (int i = 0; i < 27; i = i + 1) {
    int success;

    if (use_fork) {
      int status;
      waitpid(p[i], &status, NULL);

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