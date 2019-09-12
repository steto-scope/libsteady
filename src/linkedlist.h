#ifndef LLIST_H
#define LLIST_H

typedef struct LLNODE {
	struct LLNODE *prev;
	struct LLNODE *next;
	void *data;
} LinkedList;

LinkedList* llist_create();

#endif