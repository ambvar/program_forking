/* ----------------------------------------------------------- */
/* NAME : Amber Varacalli                    User ID: acvaraca */
/* DUE DATE : 09/28/2018                                       */
/* PROGRAM ASSIGNMENT 1                                        */
/* FILE NAME : prog1.c                                         */
/* PROGRAM PURPOSE :                                           */
/*    This program uses a main function to fork 4 child        */
/*    processes.  Those four child processes solve various     */
/*    problems including - calculating Fibonacci number,       */
/*    solving Buffon's needle problem, finding the area of     */
/*    an ellipse, and simulating a pinball game.               */
/* ----------------------------------------------------------- */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int * pinball (int bins, int balls);
int ellipse(int points, int a, int b);
int buffon (int r);
long fib (int num);

/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This function is the main function and sets up the rest */
/*     of the program.                                         */
/* PARAMETER USAGE :                                           */
/*    argc: the number of command line arguments passed in     */
/*    argv: an array of command line arguments                 */
/* FUNCTION CALLED :                                           */
/*    long fib(int x)                                          */
/*    int buffon(int r)                                        */
/*    int * pinball (int bins, int balls)                      */
/*    int ellipse(int points, int a, int b)                    */
/* ----------------------------------------------------------- */
int main (int argc, char *argv[]) {

  // Grabbing the values from the command line to use
  int n = atoi(argv[1]);
  int r = atoi(argv[2]);
  int a = atoi(argv[3]);
  int b = atoi(argv[4]);
  int s = atoi(argv[5]);
  int x = atoi(argv[6]);
  int y = atoi(argv[7]);

  // Initializing PIDs for the children
  pid_t fibPid;
  pid_t buffPid;
  pid_t areaPid;
  pid_t pinPid;

  // Main buffer
  char mainBuf [100];

  printf("Main Process Started\n");
  printf("Fibonacci Input            = %d\n", n);
  printf("Buffon's Needle Iterations = %d\n", r);
  printf("Total random number Pairs  = %d\n", s);
  printf("Semi-Major Axis Length     = %d\n", a);
  printf("Semi-Minor Axis Length     = %d\n", b);
  printf("Number of Bins             = %d\n", x);
  printf("Number of Ball Droppings   = %d\n", y);

  // Fork a child for Fibonacci
  if ((fibPid = fork()) == -1) {
    printf("Failed to fork Fibonacci.\n");
    return 1;
  } else if (fibPid == 0) {

    // Buffer for Fibonacci
    char fibBuf [1000];

    // Process has started, output
    sprintf(fibBuf, "   Fibonaci Process Started\n");
    write(1, fibBuf, strlen(fibBuf));

    sprintf(fibBuf, "   Input Number %d\n", n);
    write(1, fibBuf, strlen(fibBuf));

    // Starting Fibonacci
    long fibOut = fib(n);

    // Process has ended, output
    sprintf(fibBuf, "   Fibonacci Number f(%d) is %ld\n", n, fibOut);
		write(1, fibBuf, strlen(fibBuf));

		sprintf(fibBuf, "   Fibonacci Process Exits\n");
		write(1, fibBuf, strlen(fibBuf));

    exit(0);
  }

  sprintf(mainBuf, "Fibonacci Process Created\n");
	write(1, mainBuf, strlen(mainBuf));

  if ((buffPid = fork()) == -1) {
    printf("Failed to fork Buffon's Needle\n");
    return 1;
  } else if (buffPid == 0) {

    //Buffer for Buffon
    char buffBuf [100];

    // Process has started, output
    sprintf(buffBuf, "      Buffon's Needle Process Started\n");
    write(1, buffBuf, strlen(buffBuf));

    sprintf(buffBuf, "      Input Number %d\n", r);
    write(1, buffBuf, strlen(buffBuf));

    // Buffon's needle started
    int count = buffon(r);

    // Outputting thre probability found with buffons
    sprintf(buffBuf, "      Estimated Probability is %.4f\n", (double)count/(double)r);
		write(1, buffBuf, strlen(buffBuf));

    sprintf(buffBuf, "      Buffon's Needle Process Exits\n");
    write(1, buffBuf, strlen(buffBuf));

    exit(0);
  }

  sprintf(mainBuf, "Buffon's Needle Process Created\n");
	write(1, mainBuf, strlen(mainBuf));


  if ((areaPid = fork()) == -1) {
    printf("Failed to fork Ellipse Area");
    return 1;
  } else if (areaPid == 0) {

    char areaBuf [100];

    // Process has started, output
    sprintf(areaBuf, "         Ellipse Area Process Started\n");
    write(1, areaBuf, strlen(areaBuf));

    sprintf(areaBuf, "         Total random Number Pairs %d\n", s);
    write(1, areaBuf, strlen(areaBuf));

    sprintf(areaBuf, "         Semi-Major Axis Length %d\n", a);
    write(1, areaBuf, strlen(areaBuf));

    sprintf(areaBuf, "         Semi-Minor Axis Length %d\n", b);
    write(1, areaBuf, strlen(areaBuf));

    int hits = ellipse(s, a, b);

    sprintf(areaBuf, "         Total Hits %d\n", hits);
    write(1, areaBuf, strlen(areaBuf));

    // Calculating the estimated area based on the input and random hits
    float estimated = (((float)hits/(float)s) * (float)a * (float)b) * 4.0;

    sprintf(areaBuf, "         Estimated Area is %5.4f\n", estimated);
    write(1, areaBuf, strlen(areaBuf));

    // Calculating the actual area
    float actual = (float)M_PI * (float)a * (float)b;

    sprintf(areaBuf, "         Actual Area is %5.4f\n", actual);
    write(1, areaBuf, strlen(areaBuf));

    exit(0);

  }

  sprintf(mainBuf, "Ellipse Area Process Created\n");
  write(1, mainBuf, strlen(mainBuf));


  if ((pinPid = fork()) == -1) {
    printf("Failed to fork Simple Pinball\n");
    return 1;
  } else if (pinPid == 0) {

    //Buffer for pinball
    char pinBuf [1100];

    sprintf(pinBuf, "Simple Pinball Process Started\n");
		write(1, pinBuf, strlen(pinBuf));

    sprintf(pinBuf, "Number of Bins %d\n", x);
		write(1, pinBuf, strlen(pinBuf));

    sprintf(pinBuf, "Number of Ball Droppings %d\n", y);
		write(1, pinBuf, strlen(pinBuf));

    // Starting pinball game
    int * pinOut = pinball(x, y);

    // Initialzing some variables
    int i, j;
    char tmpBuf[1000];
    float per;
    char graph [50];

    // Finding the highest percentage of balls in a basket
    float high = 0.0;
    for (i = 0; i < x; i++) {
      per = (float)(*(pinOut + i)/(float)y) * 100.0;
      if (per > high) {
        high = per;
      }
    }

    // After finding the high, adding in the correct amount of asterikes for the graph
    for (i = 0; i < x; i++) {
      per = (float)(*(pinOut + i)/(float)y) * 100.0;
      int limit = (per/high) * 50;
      for (j = 0; j < limit; j++) {
        graph[j] = '*';
      }
      graph[j] = '\0';

      // Outputting the graph results and emptying graph
      sprintf(pinBuf, "%3d- (%7d) - ( %5.2f%c) | %s\n", (i + 1), *(pinOut + i), per, '%', graph);
      write(1, pinBuf, strlen(pinBuf));
      memset(graph, 0, 50 * (sizeof graph[0]) );
    }

   sprintf(pinBuf, "Simple Pinball Process Exits\n");
   write(1, pinBuf, strlen(pinBuf));

   exit(0);

  }

  sprintf(mainBuf, "Simple Pinball Process Created\n");
  write(1, mainBuf, strlen(mainBuf));

  sprintf(mainBuf, "Main Process Waits\n");
	write(1, mainBuf, strlen(mainBuf));

  // Waiting for all the children to finish
  wait(NULL);
  wait(NULL);
  wait(NULL);
  wait(NULL);

  sprintf(mainBuf, "Main Process Exits\n");
  write(1, mainBuf, strlen(mainBuf));

  return 0;

}

/* ----------------------------------------------------------- */
/* FUNCTION  pinball                                           */
/*     determines how many balls will drop into each basket    */
/*      after falling down the pins.                           */
/* PARAMETER USAGE :                                           */
/*    int bins: amount of bins that will catch the balls       */
/*    int balls: amout of balls that will be dropped           */
/* FUNCTION CALLED :                                           */
/*    [CALLS NO FUNCTIONS]                                     */
/* ----------------------------------------------------------- */
int * pinball (int bins, int balls) {
  int * counter = malloc(bins * sizeof(int));
  int treeLen = 0;
  int tmp = 1;

  // Finding the amount of nodes based on how many bins there are
  //    treeLen DOES NOT include the bins as the last row.
  while (tmp != bins) {
    treeLen += tmp;
    tmp += 1;
  }

  // Array for the tree of pins
  // int pins [treeLen + bins];
  int * pins = malloc((treeLen + bins) * sizeof(int));
  int i;
  for (i = 0; i < treeLen; i++) {
    pins[i] = i + 1;
  }

  // Put in basket numbers to the array so we can keep track of them
  int b = 1;
  for (i = 0; i < bins; i++) {
    pins[treeLen + i] = b;
    b += 1;
  }

  // Looping through all the dropped and simulating the ball dropping through
  //  pins
  int pin, dropped = 0;
  while (dropped <= balls) {
    int row;
    for (row = 1; row < bins; row++) {
      pin = (rand() % (2 - 0) == 0) ? pin + row : pin + row + 1;
    }
    counter[pins[pin] - 1] += 1;
    pin = 0;
    dropped += 1;
  }

  return counter;
}

/* ----------------------------------------------------------- */
/* FUNCTION  ellipse                                           */
/*     returns the amount of points that are within the        */
/*     given ellipse                                           */
/* PARAMETER USAGE :                                           */
/*    int points: the number of randomly generated points to   */
/*           be tested if it exists in the ellipse             */
/*    int a: length of the semi-major axis                     */
/*    int b: length of the semi-minor axis                     */
/* FUNCTION CALLED :                                           */
/*    [CALLS NO FUNCTIONS]                                     */
/* ----------------------------------------------------------- */
int ellipse(int points, int a, int b) {
  float x, y;
  int hits = 0;

  int i;
  srand(time(NULL));
  for (i = 0; i < points; i++) {

    // Generate the random numbers and check if value is equal or less than 1
    x = (float)rand()/(float)(RAND_MAX/a);
    y = (float)rand()/(float)(RAND_MAX/b);
    if (((pow(x, 2)/pow(a, 2)) + (pow(y, 2)/pow(x, 2))) <= 1) {
      hits += 1;
    }

  }
	return hits;
}

/* ----------------------------------------------------------- */
/* FUNCTION  buffon                                            */
/*     calculates the probability for Buffon's Needle problem  */
/*     with assumed needle and grid distance of 1              */
/* PARAMETER USAGE :                                           */
/*    int r: the number of times the needle needs to be thrown */
/* FUNCTION CALLED :                                           */
/*    [CALLS NO FUNCTIONS]                                     */
/* ----------------------------------------------------------- */
int buffon(int r) {
	double d, a;
	int t = 0;

	const double pi = acos(-1);

  // Simulating throwing the needle
	srand(time(NULL));
	int throws = 0;
	while(throws < r) {
		d = ((float)rand())/RAND_MAX;
		a = rand()/(RAND_MAX/(2*pi));

		double val = d + (sin(a));

		if(val < 0 || val > 1) {
			t++;
		}

		throws++;

	}
	return t;
}

/* ----------------------------------------------------------- */
/* FUNCTION  fib                                               */
/*     calculates the n'th Fibonacci number recursively        */
/* PARAMETER USAGE :                                           */
/*    int num: which Fib number to compute                     */
/* FUNCTION CALLED :                                           */
/*    long fib(int num)                                        */
/* ----------------------------------------------------------- */
long fib (int num) {
  // Fibonacci recursively
  if(num == 1 || num == 2) {
		return 1;
	}
	return fib(num - 1) + fib(num - 2);
}
