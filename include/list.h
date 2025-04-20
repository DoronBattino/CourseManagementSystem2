
#ifndef LIST_MTM_H
#define LIST_MTM_H

#include <stdbool.h>

typedef enum{
    LIST_SUCCESS,
    LIST_NULL_ARGUMENT,
    LIST_INVALID_CURRENT,
    LIST_OUT_OF_MEMORY
}ListResult;

typedef struct List_t *List;
typedef struct node *Node;
typedef void * ListElement;
typedef void * ListFilterKey;
typedef void * ListSortKey;

typedef void *(*CopyListElement)(void *);
typedef void (*FreeListElement)(void *);
typedef int (*CompareListElements)(void *, void *, ListSortKey key);
typedef bool (*FilterListElement)(ListElement element, ListFilterKey key);

struct List_t {
	Node head;
	Node iterator;
    CompareListElements compareElements;
	CopyListElement copyElement;
	FreeListElement freeElement;
};



List listCreate(CopyListElement copyElement, FreeListElement freeElement);
int listGetSize(List list);
List listCopy(List list);
ListElement listGetFirst(List list);
ListElement listGetNext(List list);
ListElement listGetCurrent(List list);
ListResult listInsertFirst(List list, ListElement element);
ListResult listInsertLast(List list, ListElement element);
ListResult listInsertBeforeCurrent(List list, ListElement element);
ListResult listInsertAfterCurrent(List list, ListElement element);
ListResult listRemoveCurrent(List list);
ListResult listSort(List list, CompareListElements compareElement, ListSortKey key);
List listFilter(List list, FilterListElement filterElement, ListFilterKey key);
ListResult listClear(List list);
void listDestroy(List list);

#define LIST_FOREACH(type,iterator,list) \
	for(type iterator = listGetFirst(list) ; \
		iterator ;\
		iterator = listGetNext(list))

#endif