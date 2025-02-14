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

  //read all the input
  for (int i = 0; i < BOARDSIZE; i = i + 1) {
    scanf("%d", &solution[i]);
    // printf("%d\n", solution[i]);
  }


  //create a boat load of threads or forks
  struct Mission mission[9+9+9];

  //rows
  for (int i = 0; i < 9; i = i + 1) {
    mission[i].array = solution;
    mission[i].id = i;
    if (use_fork) {

    }
    else {
      pthread_create(&thread[i], NULL, rowGrabber, &mission[i]);
    }
  }

  //columns
  for (int i = 0; i < 9; i = i + 1) {
    mission[i+9].array = solution;
    mission[i+9].id = i;
    if (use_fork) {

    }
    else {
      pthread_create(&thread[i+9], NULL, columnGrabber, &mission[i+9]);
    }
  }

  //columns
  for (int i = 0; i < 9; i = i + 1) {
    mission[i+18].array = solution;
    mission[i+18].id = i;
    if (use_fork) {

    }
    else {
      pthread_create(&thread[i+18], NULL, gridGrabber, &mission[i+18]);
    }
  }

  //collect answers
  int valid = 1;
  for (int i = 0; i < (9+9+9); i = i + 1) {
    if (use_fork) {

    }
    else {
      void* retVal;
      pthread_join(thread[i], retVal);
      valid &= *((int*)retVal);
    }
  }

  //tell the user whether they're an idiot
  if (valid) {
    printf("The input is a valid Sudoku.\n");
  }

  return 0;
}
