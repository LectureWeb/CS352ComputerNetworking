/*
	parse tokens without allocating buffers and copying strings
	For the parsing used here, you can use strtok() to accomplish
	the same thing. For other types of parsing, strtok() may
	not be sufficient.

	Paul Krzyzanowski
*/

#include <stdio.h> 
#define MAXTOKENS 256

int
main(int argc, char **argv)
{
	char name[] = "//abc/def////ghi/jkl";	/* test string */
	char *item[MAXTOKENS];	/* this holds our array of tokens */
	char separator = '/';
	char *s;	/* where we're scanning */
	int i=0;	/* current item */

	for (s=name; *s == separator; s++) ;	/* skip initial separators */

	item[i] = s;	/* first token */
	for (; *s; s++) {
		if (*s == separator) {		/* end of item */
			*s = 0;		/* mark end of string */
			while (*(s+1) == separator) s++;	/* skip all separators */
			item[++i] = s+1;
		}
	}

	/* print our list of tokens */
	int j;
	for (j=0; j <= i; j++) 
		printf("item %d: \"%s\"\n", j, item[j]);
}
