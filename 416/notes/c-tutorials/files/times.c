/* times: report times used by the current process */
/* Paul Krzyzanowski */

#include <stdio.h>		/* defines printf() */
#include <stdlib.h>		/* to define exit() */
#include <unistd.h>		/* for sysconf() */
#include <stdint.h>		/* used for casting clock_t to uintmax_t for printf */
#include <sys/times.h>		/* needed for the times() system call */
#include <sys/types.h>
#include <sys/stat.h>		/* used for open() */
#include <fcntl.h>		/* used for open() */

void kill_time(void);

int
main(int argc, char **argv) {
	struct tms t;	/* the time values will be placed into this struct */

	printf("tick frequency is: %lu\n", sysconf(_SC_CLK_TCK));

	kill_time();		/* do something to use up some time */
	if (times(&t) < 0) {
		perror("times");	/* error - print a message and exit */
		exit(1);
	}
	/* print the results */
	printf("user time: %ju ticks\n", (uintmax_t) t.tms_utime);
	printf("system time: %ju ticks\n", (uintmax_t) t.tms_stime);
	printf("chidren - user time: %ju ticks\n", (uintmax_t) t.tms_cutime);
	printf("chidren - system time: %ju ticks\n", (uintmax_t) t.tms_cstime);

	exit(0);
}

void
kill_time(void) {
	long long i, j;	/* use these in a loop to kill time */
	int fd;
	char buf[2048];

	printf("doing some cpu wasting stuff\n");
	for (i=0; i<100000000; i++)
		j += i;

	printf("doing some kernel wasting stuff\n");
	/* do some stuff to waste system time */
	if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
		perror("open");
		exit(1);
	}
	for (i=0; i < 1000; i++) 
		read(fd, buf, 2048);
	close(fd);
}
