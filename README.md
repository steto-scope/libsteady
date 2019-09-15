# STEfan's All-purpose Datastructure librarY (libsteady)

This library contains a set of common datastructures for use in C applications without relying on the existence of external assemblies. Each datastructure is standalone in its own source/header file pair and can be used in several ways:
 * collectively as a compiled static library (libsteady.a)
 * individualy as part of the using project's makefile

 Each datastructure comes with a set of automated tests for maximum stability.

## Available Datastructures

* Linked List

## Compiling

```
autoreconf --install
./configure
./make
```

link `src/libsteady.a` in your project and include the appropriate header file(s) found in `src/`.

For the test suite, run `tests/test_libsteady`.


## Quick API Reference

### <a name="LList"></a> Linked List (LList)

```C
typedef struct LLNODE {
	struct LLNODE *next;
	void *data;
} LNode;

typedef struct LLIST {
	struct LLNODE *head;
	struct LLNODE *tail;
	int size;
} LList;

LList* llist_create();
int llist_insert(LList *list, int pos, void *data);
int llist_append(list, data);
int llist_prepend(list, data);	
int llist_remove(LList *list, int index);
int llist_indexof(LList *list, void *data);
void llist_print(LList *list, char *format);
void llist_print_cb(LList *list, void (*callback)(void*));
void* llist_get(LList *list, int index);
int llist_append(list, data);
int llist_prepend(list, data);	
```