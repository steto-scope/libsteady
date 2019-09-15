#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

#include "linkedlist.h"


LList* llist_create()
{
	LList *l;

	l = (LList*)malloc(sizeof(LList));
	if(l == NULL) {
		return NULL;
	}	

	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

int llist_insert(LList *list, int pos, void *data)
{
	LNode *n;
	LNode *o;
	uint i;	

	if(list == NULL || pos < 0) {
		return 0;
	}

	n = (LNode*)malloc(sizeof(LNode));
	if(n == NULL) {
		return 0;
	}
	n->data = data;

	if(list->size < 1) {
		list->head = n;
		list->tail = n;
		list->size++;
	} 
	else if(pos == 0) {
		n->next = list->head;
		list->head = n;
		list->size++;
	}
	else if(pos >= list->size) {
		list->tail->next = n;
		list->tail = list->tail->next;
		list->size++;
	} 
	else {
		o = list->head;
		for(i=0; i<pos && o != NULL; i++) {
			o = o->next;
		}
		n->next = o->next;
		o->next = n;
		list->size++;
	}
	return 1;
}

int llist_indexof(LList *list, void *data)
{
	LNode *n;
	int i;

	if(list == NULL || list->head == NULL){
		return -1;
	}

	n = list->head;
	i = 0;
	do {
		if(n->data == data) {
			return i;
		}
		n = n->next;
		i++;
	} 
	while(n != NULL);

	return -1; 
}

void* llist_get(LList *list, int index)
{
	LNode *n;

	if((list == NULL) || (index >= list->size) || (index < 0)){
		return NULL;
	}

	n = list->head;
	for(; index > 0; index--) {
		n = n->next;
	}

	return n->data;
}

int llist_remove(LList *list, int index)
{
	LNode *n, *p;

	if((list == NULL) || (index < 0) || (index >= list->size) || (list->size < 1)) {
		return 0;
	}

	p = NULL;
	n = list->head;

	for(; index>0; index--) {
		p = n;
		n = n->next;
	}

	if(p == NULL) {
		list->head = n->next;
		free(n);
	} else {
		p->next = n != NULL ? n->next : NULL;
		free(n);
	}
	list->size--;

	return 1;
}

void llist_print(LList *list, char *format)
{
	LNode *n;

	printf("List(%d)", list->size);
	n = list->head;
	if(list->size > 0) {
		do {
			printf(" -> ");
			printf(format, n->data);
		}
		while((n = n->next) != NULL);
	}
	printf("\n");
}

void llist_print_cb(LList *list, void (*callback)(void*))
{
	LNode *n;

	printf("List(%d)", list->size);
	n = list->head;
	if(list->size > 0) {
		do {
			printf(" -> ");
			callback(n->data);
		}
		while((n = n->next) != NULL);
	}
	printf("\n");
}