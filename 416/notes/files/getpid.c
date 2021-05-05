#include <stdio.h>
#include <stdlib.h>

main() {
	printf("my pid is %d\n", getpid());
	printf("my parent’s pid is %d\n", getppid());
	printf("I’m in group %d\n", getpgrp());
}

