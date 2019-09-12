#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "linkedlist.h"

LinkedList* llist_create()
{
	LinkedList *l;

	l = (LinkedList*)malloc(sizeof(LinkedList));
	if(l == NULL) {
		return NULL;
	}
	return l;
}