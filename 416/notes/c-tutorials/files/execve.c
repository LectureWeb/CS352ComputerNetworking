/* execve: run a program */
/* Paul Krzyzanowski */

#include <stdlib.h>	/* needed to define exit() */
#include <unistd.h>	/* needed to define getpid() */
#include <stdio.h>	/* needed for printf() */

int
main(int argc, char **argv) {
	char *args[] = {"ls", "-aF", "/", 0};	/* each element represents a command line argument */
	char *env[] = { 0 };	/* leave the environment list null */

	printf("About to run /bin/ls\n");
	execve("/bin/ls", args, env);
	perror("execve");	/* if we get here, execve failed */
	exit(1);
}
