/* times: use gettimeofday() to get the elapsed time */
/* Paul Krzyzanowski */

#include <stdio.h>		/* declares printf() */
#include <stdlib.h>		/* declares exit() */
#include <stdint.h>		/* used for casting clock_t to uintmax_t for printf */
#include <sys/time.h>		/* needed for the gettimeofday() system call */

int
main(int argc, char **argv) {
	struct timeval start;	/* starting time */
	struct timeval end;	/* ending time */
	unsigned long e_usec;	/* elapsed microseconds */

	gettimeofday(&start, 0);	/* mark the start time */
	sleep(2);		/* sleep for 2 seconds */
	gettimeofday(&end, 0);		/* mark the end time */

	/* now we can do the math. timeval has two elements: seconds and microseconds */
	e_usec = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);

	printf("elapsed time: %lu microseconds\n", e_usec);
	exit(0);
}
