#ifndef LLIST_H
#define LLIST_H


typedef struct LLNODE {
	struct LLNODE *next;
	void *data;
} LNode;

typedef struct LLIST {
	struct LLNODE *head;
	struct LLNODE *tail;
	int size;
} LList;

/**
 * creates a new Linked List 
 * @return LList* new instance or NULL if not sufficient memory
 */
LList* llist_create();
/**
 * Inserts a new element into the Linked List
 * @param LList* the list to add to
 * @param int position index
 * @param void* data to be added
 * @return 1 if successful, 0 if failed
 */
int llist_insert(LList *l, int pos, void *data);
/**
 * Removes an new element from the Linked List
 * @param LList* the list to remove from
 * @param int position index
 * @return 1 if successful, 0 if failed
 */
int llist_remove(LList *list, int index);
/**
 * Gets the index of the first occourence of an element
 * @param LList* the list to check
 * @param void* data to be searched after
 * @return -1 on failure or list index
 */
int llist_indexof(LList *list, void *data);
/**
 * Prints a Linked List in a human readable format
 * @param LList* the list to print
 * @param char* printf format string for the data elements
 */
void llist_print(LList *list, char *format);
/**
 * Prints a Linked List in a human readable format
 * @param LList* the list to print
 * @param void()(void*) callback function that handles the element output
 */
void llist_print_cb(LList *list, void (*callback)(void*));
/**
 * Gets the element on a given list index
 * @param LList* the list to retrieve from
 * @param int index of the element
 */
void* llist_get(LList *list, int index);
/**
 * Absorbes the nodes of a list into another and frees it
 * @param LList* the list to insert into
 * @param int position of the insertion
 * @param LList* the list to be absorbed. 
 * 	  After execution this LList-Pointer will be freed and set to NULL
 * @return 0 on error, otherwise 1. Absorbing NULL is not considered an error
 */
int llist_absorb(LList *list, int index, LList *secondList);
/**
 * Frees a linked list shallow
 * @param LList* the list to be free'd
 */
void llist_free(LList *list);

#define llist_append(list, data)	llist_insert(list, list->size, (void*)data)
#define llist_prepend(list, data)	llist_insert(list, 0, (void*)data)

#endif