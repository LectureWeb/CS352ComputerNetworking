/* times: use clock() to get the elapsed time */

#include <stdio.h>		/* declares printf() */
#include <stdlib.h>		/* declares exit() */
#include <stdint.h>		/* used for casting clock_t to uintmax_t for printf */
#include <time.h>		/* needed for the clock() library function */

int
main(int argc, char **argv) {
	unsigned long freq;	/* clock frequency */
	uintmax_t start;	/* starting tick value */
	uintmax_t end;		/* ending tick value */

	start = clock(); 	/* mark the start time */
	sleep(2);	/* sleep for two seconds */
	end = clock(); 		/* mark the end time */

	printf("elapsed time: %ju - %ju = %ju ticks\n", end, start, end-start);
	printf("elapsed time: %8.6f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
	exit(0);
}
