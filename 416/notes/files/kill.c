#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

main(int argc, char **argv)
{
	if (fork())		/* fork, assume it always works */
		for (;;)	/* parent prints a message forever */
			printf("I’m the parent\n");
	else {	/* we’re the child */
		sleep(3);	/* do nothing for three seconds */
		kill(getppid(), SIGKILL);	/* kill the parent */
	}
}
