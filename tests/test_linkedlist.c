#include <check.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdarg.h>
#include "sput.h"
#include "../src/linkedlist.h"

int lval(LList *l, int size, ...)
{
	va_list va;
	LNode *n;
	void *v;

	if(l == NULL || size < 0) {
		return 0;
	}
	if(l->size != size) {
		return 0;
	}

	n = l->head;
	if(n == NULL) {
		return size == 0;
	}

	va_start(va, size);
	do
	{
		
		v = va_arg(va, void*);
		if(n->data != v) {
			va_end(va);
			return 0;
		}
		n = n->next;
		size--;
		
	}while(v != 0 && size > 0);

	va_end(va);
	return 1;
}

void test_llist_create()
{
	LList *l;

	l = llist_create();

	sput_fail_unless(lval(l,0), "Node Creation");
}

void test_llist_insert()
{
	int ret;
	LList *l;
	LNode *e1, *e2, *e3;

	l = llist_create();
	
	ret = llist_insert(l, 0, (void*)42);	
	sput_fail_unless(lval(l, 1, 42) && ret, "Insert at Head");	
	sput_fail_if(l->head != l->tail, "Node Status");	
	
	ret = llist_insert(l, 0, (void*)420);
	sput_fail_unless(lval(l, 2, 420, 42) && ret, "Repeated Insert at Head");
	sput_fail_if(l->head == l->tail || l->tail == NULL, "Node Status");
	
	ret = llist_insert(l, 69, (void*)666);
	sput_fail_unless(lval(l, 3, 420, 42, 666) && ret, "Exceeding position");
	sput_fail_if(l->head == l->tail || l->tail == NULL, "Node Status");

	ret = llist_insert(l, -8, (void*)111);
	sput_fail_unless(lval(l, 3, 420, 42, 666) && !ret, "Invalid position");
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

void test_llist_absorb()
{
	LList *l, *l2;
	int r1, r2, r3, r4;

	l = llist_create();	
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)100);
	l2 = llist_create();
	llist_append(l2, (void*)42);
	r1 = llist_absorb(l, -1, l2);
	sput_fail_unless(lval(l, 3, 10, 100, 100) && !r1, "Invalid index");
	llist_free(l);
	//llist_free(l2);


	l = llist_create();	
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)100);
	l2 = llist_create();
	llist_append(l2, (void*)42);
	r1 = llist_absorb(NULL, 0, l2);
	sput_fail_unless(!lval(NULL, 1, 42) && !r1, "Invalid list");
	llist_free(l);
	//llist_free(l2);
	

	l = llist_create();	
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)100);
	l2 = llist_create();
	llist_append(l2, (void*)42);
	r1 = llist_absorb(l, 0, l2);
	sput_fail_unless(lval(l, 4, 42, 10, 100, 100) && r1, "at head");
	llist_free(l);


	l = llist_create();	
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)100);
	l2 = llist_create();
	llist_append(l2, (void*)42);
	r1 = llist_absorb(l, 44, l2);
	sput_fail_unless(lval(l, 4, 10, 100, 100, 42) && r1, "at tail");
	llist_free(l);


	l = llist_create();	
	llist_append(l, (void*)10);
	llist_append(l, (void*)100);
	llist_append(l, (void*)100);
	l2 = llist_create();
	llist_append(l2, (void*)42);
	r1 = llist_absorb(l, 1, l2);
	sput_fail_unless(lval(l, 4, 10, 42, 100, 100) && r1, "in between");
	llist_free(l);
	//llist_print(l, "%d(%d)");
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
	sput_run_test(test_llist_absorb);
	
	sput_finish_testing();

	return sput_get_return_value();
}
