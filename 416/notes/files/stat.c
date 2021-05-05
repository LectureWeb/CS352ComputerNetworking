#include <stdio.h>	/* for printf */
#include <sys/stat.h>   /* stat wants this */

main(int argc, char **argv) {
	struct stat buf;
	while (*++argv)  /* for each argument… */
		if (stat(*argv, &buf) != -1) {
			if (buf.st_mode & S_IFREG)      /* check the mode fo the file */
				printf("%s: %lu bytes\n", *argv, (unsigned long)buf.st_size);
			else
				printf("%s: not a regular file\n", *argv);
		}
		else /* system call failed */
			perror(*argv);
}

