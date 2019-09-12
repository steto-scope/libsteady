#include "sput.h"

int run_llist_tests(void);

int main(int argc, char *argv[])
{
	int res = EXIT_SUCCESS;

	res |= run_llist_tests();

	return res;
}