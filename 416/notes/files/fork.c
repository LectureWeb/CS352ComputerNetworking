#include <stdio.h>
#include <stdlib.h>

main(int argc, char **argv) {
	switch (fork()) {
	case 0:
		printf("I'm the child: pid=%d\n", getpid());
		break;
	default:
		printf("I'm the parent: pid=%d\n", getpid());
		break;
	case -1:
		perror("fork");
	}
}
