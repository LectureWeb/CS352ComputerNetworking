/* an example that dereferences a null pointer */
/* Paul Krzyzanowski */

int
main(int argc, char **argv) {
	int a;

	a = *(int *)0;	/* read address 0 */
}
