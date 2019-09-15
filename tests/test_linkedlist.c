#include <check.h>
#include <stdlib.h>

#include <stdio.h>
#include "sput.h"
#include "../src/linkedlist.h"

void test_llist_create()
{
	LList *l;

	l = llist_create();

	sput_fail_if(	l == NULL ||
			l->head != NULL ||
			l->tail != NULL ||
			l->size != 0
			, "Node Creation");
}

void test_llist_insert()
{
	int ret;
	LList *l;
	LNode *e1, *e2, *e3;

	l = llist_create();
	
	ret = llist_insert(l, 0, (void*)42);
	

	sput_fail_if(	l == NULL ||
			l->head == NULL ||
			l->tail == NULL ||
			l->head->data != (void*)42 ||
			l->size != 1 ||
			ret != 1
			, "Insert at Head");

	
	ret = llist_insert(l, 0, (void*)420);
	

	e1 = l->head;
	e2 = l->head->next;
	sput_fail_if(	e1->data != (void*)420 ||
			e2->data != (void*)42 ||
			l->size != 2 ||
			ret != 1
			, "Element Order");


	ret = llist_insert(l, 69, (void*)666);

	e1 = l->head;
	e2 = l->head->next;
	e3 = e2->next;
	sput_fail_if(	e1->data != (void*)420 ||
			e2->data != (void*)42 ||
			e3->data != (void*)666 ||
			l->size != 3 ||
			ret != 1
			, "Exceeding position");

	ret = llist_insert(l, -8, (void*)111);

	e1 = l->head;
	e2 = l->head->next;
	e3 = e2->next;
	sput_fail_if(	e1->data != (void*)420 ||
			e2->data != (void*)42 ||
			e3->data != (void*)666 ||
			l->size != 3 ||
			ret != 0
			, "Invalid position");
}

void test_llist_indexof()
{
	LList *l;
	int r1, r2, r3, r4;

	l = llist_create();
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)100);

	r1 = llist_indexof(l, (void*)1);
	r2 = llist_indexof(l, (void*)10);
	r3 = llist_indexof(l, (void*)100);
	r4 = llist_indexof(l, (void*)100);

	sput_fail_if(	r1 != -1 ||
			r2 != 0 ||
			r3 != 1 ||
			r4 != 1
			, "Index of");
}


void test_llist_get()
{
	LList *l;
	int r1, r2, r3, r4;

	l = llist_create();
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);

	sput_fail_if(llist_get(NULL, 0) != NULL, "Non-existent List");
	sput_fail_if(llist_get(l, -1) != NULL, "Too small index");
	sput_fail_if(llist_get(l, 0) != (void*)10, "First");
	sput_fail_if(llist_get(l, 1) != (void*)100, "Second");
	sput_fail_if(llist_get(l, 2) != NULL, "Too big index");
}

void test_llist_remove()
{
	LList *l;

	l = llist_create();
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)1000);

	sput_fail_if(llist_remove(l, l->size), "Too big index");
	sput_fail_if(llist_remove(l, -1), "Too small index");
	sput_fail_if(!llist_remove(l, 2), "Remove at tail");
	sput_fail_if(l->size != 2, "Size update");
	sput_fail_if(!llist_remove(l, 0), "Remove at head");
	sput_fail_if(!llist_remove(l, 0), "Remove last element");
	sput_fail_if(llist_remove(l, 0), "Remove from empty list");
	sput_fail_if(llist_remove(NULL, 0), "Remove from non-existing list");
}

int run_llist_tests(void)
{
	sput_start_testing();

	sput_enter_suite("Linked List");
	sput_run_test(test_llist_create);
	sput_run_test(test_llist_insert);
	sput_run_test(test_llist_indexof);
	sput_run_test(test_llist_get);
	sput_run_test(test_llist_remove);
	
	sput_finish_testing();

	return sput_get_return_value();
}
