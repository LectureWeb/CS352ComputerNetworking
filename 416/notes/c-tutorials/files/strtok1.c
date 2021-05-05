#include <stdio.h>
#include <string.h>	/* needed for strtok */

main(int argc, char **argv) {
	char text[] = "Cut-down---a----tree++with-a-herring";
	char *t;
	int i;

	t = strtok(text, "-+");
	for (i=0; t != NULL; i++) {
		printf("token %d is \"%s\"\n", i, t);
		t = strtok(NULL, "-+");
	}
}
