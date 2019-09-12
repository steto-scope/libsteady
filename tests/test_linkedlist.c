#include <check.h>
#include <stdlib.h>

#include <stdio.h>
#include "sput.h"
#include "../src/linkedlist.h"

void test_llist_create()
{
	LinkedList *list;

	list = llist_create();

	sput_fail_unless(list != NULL, "Node Creation");
}

int run_llist_tests(void)
{
	sput_start_testing();

	sput_enter_suite("Linked List");
	sput_run_test(test_llist_create);
	
	sput_finish_testing();

	return sput_get_return_value();
}
