/* list: linked list example */
/* Paul Krzyzanowski */

#include <stdlib.h>	/* needed to define malloc() */
#include <string.h>	/* needed to define strdup() */
#include <stdio.h>	/* needed for printf() */
#define MAXLEN 128

struct list_entry {
	char *data;
	struct list_entry *next;
} *list = (struct list_entry *)0;

int
main(int argc, char **argv) {
	void dump(void);
	char *s, line[MAXLEN];
	struct list_entry *item;

	while (fgets(line, MAXLEN, stdin) != 0) {	/* read until eof or . */
		/* fgets reads in a \n - strip it */
		if ((s = strchr(line, '\n')) != 0)
			*s = 0;

		if (strcmp(line, ".") == 0) 	/* we have a line with just "." */
			break;

		/* allocate a new list element */
		item = malloc(sizeof(struct list_entry));
		if (item == 0) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
		/* set the data in the list element */
		item->data = strdup(line);	/* copy the string */
		item->next = list;

		/* we have a new head of the list */
		list = item;
	}
	dump();
	exit(0);
}

/* dump: dump the list */

void
dump(void) 
{
	struct list_entry *lp;
	
	for (lp = list; lp != 0; lp=lp->next)
		printf("item: \"%s\"\n", lp->data);	
}
