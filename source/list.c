#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


typedef struct node *Node;
struct node{
	ListElement element;
	Node next;
};



static Node createNode(){
	Node new_node = malloc(sizeof(*new_node));
	if(!new_node) return NULL;
	new_node->element = NULL;
	new_node->next = NULL;
	return new_node;
}

List listCreate(CopyListElement copyElement, FreeListElement freeElement){
	if(!copyElement || !freeElement) return NULL;
	List new_list = malloc(sizeof(*new_list));
	if(!new_list) return NULL;
	new_list->head = NULL;
	new_list->iterator = NULL;
	new_list->copyElement = copyElement;
	new_list->freeElement = freeElement;
	return new_list;
}

int listGetSize(List list){
    if(list == NULL) return -1;
    int counter=0;
    for(Node ptr=list->head;ptr != NULL; ptr=ptr->next) {
            counter++;
    }
    return counter;
}

List listCopy(List list){
	if(list==NULL) return NULL;
	List new_list = listCreate(list->copyElement, list->freeElement);
	if(!new_list) return NULL;
	new_list->head = createNode(); //DUMMY
	Node ptr = NULL;
	Node prev = new_list->head;
	for(Node curr = list->head; curr; curr = curr->next){
		ptr = createNode();
		if(!ptr){
			listDestroy(new_list);
			return NULL;
		}
		ptr->element = new_list->copyElement(curr->element);
		if(!ptr->element){
			listDestroy(new_list);
			return NULL;
		}
		prev->next = ptr;
		prev = ptr;
		ptr = ptr->next;
	}
	Node tmp = new_list->head; //ERASE DUMMY
	new_list->head = new_list->head->next;
	free(tmp);
	int steps = 0;
	for(Node ptr = list->head; ptr != list->iterator; ptr = ptr->next){
		++steps;
	}
	new_list->iterator = new_list->head;
	for(int i = 0; i < steps; ++i){
		new_list->iterator = new_list->iterator->next;
	}
	return new_list;
}


ListElement listGetFirst(List list){
    if(list==NULL) return NULL;
    if(!listGetSize(list)) return NULL;
    list->iterator=list->head;
    return list->iterator->element;

}

ListElement listGetNext(List list){
    if(list==NULL) return NULL;
    if(!list->iterator) return NULL;
    if(list->iterator->next==NULL){
        list->iterator=NULL;
        return NULL;
    }
    list->iterator=list->iterator->next;
    return list->iterator->element;
}


ListElement listGetCurrent(List list){
    if(list==NULL || list->iterator==NULL) return NULL;
    return list->iterator->element;
}


ListResult listInsertFirst(List list, ListElement element){
	if(!list || !element) return LIST_NULL_ARGUMENT;
	Node new_node = createNode();
	if(!new_node) return LIST_OUT_OF_MEMORY;
	new_node->element = list->copyElement(element);
	new_node->next = list->head;
	list->head = new_node;
	return LIST_SUCCESS;
}
ListResult listInsertLast(List list, ListElement element){
	if(!list || !element) return LIST_NULL_ARGUMENT;
	Node new_node = createNode();
	if(!new_node) return LIST_OUT_OF_MEMORY;
	new_node->element = list->copyElement(element);
	new_node->next = NULL;
	Node ptr = list->head;
	if(!ptr){
		list->head = new_node;
	}else{
		while(ptr->next){
			ptr = ptr->next;
		}
			ptr->next = new_node;
		}
	return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
	if(!list || !element) return LIST_NULL_ARGUMENT;
	if(!list->iterator) return LIST_INVALID_CURRENT;
	Node ptr = list->head;
	if(list->iterator == ptr){
		ListResult lr = listInsertFirst(list, element);
		if(lr==LIST_OUT_OF_MEMORY) return LIST_OUT_OF_MEMORY;
		return LIST_SUCCESS;
	}
	Node new_node = createNode();
	if(!new_node) return LIST_OUT_OF_MEMORY;
	new_node->element = list->copyElement(element);
	while(ptr->next != list->iterator){
		ptr = ptr->next;
	}
	ptr->next = new_node;
	new_node->next = list->iterator;
	return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element){
	if(!list || !element) return LIST_NULL_ARGUMENT;
	if(!list->iterator) return LIST_INVALID_CURRENT;
	Node ptr = list->head;
	while(ptr != list->iterator){
		ptr = ptr->next;
	}
	if(!ptr->next){
		ListResult lr = listInsertLast(list,element);
		if(lr==LIST_OUT_OF_MEMORY) return LIST_OUT_OF_MEMORY;
		return LIST_SUCCESS;
	}
	Node new_node = createNode();
	if(!new_node) return LIST_OUT_OF_MEMORY;
	new_node = list->copyElement(element);
	ptr = ptr->next;
	list->iterator->next = new_node;
	new_node->next = ptr;
	return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list){
	if(!list) return LIST_NULL_ARGUMENT;
	if(!list->iterator || !list->head) return LIST_INVALID_CURRENT;
	if(list->iterator==list->head){
		list->head = list->head->next;
		list->freeElement(list->iterator->element);
		free(list->iterator);
		list->iterator = NULL;
		return LIST_SUCCESS;
	}
	Node ptr = list->head;
	while(ptr->next!=list->iterator){
		ptr = ptr->next;
	}
	if(!list->iterator->next){
		ptr->next = NULL;
		list->freeElement(list->iterator->element);
		free(list->iterator);
		list->iterator = NULL;
		return LIST_SUCCESS;
	}
	ptr->next = ptr->next->next;
	list->freeElement(list->iterator->element);
	free(list->iterator);
	list->iterator = NULL;
	return LIST_SUCCESS;
}

ListResult listSort(List list, CompareListElements compareElement,
	ListSortKey key){
	if(!list || !compareElement) return LIST_NULL_ARGUMENT;
	if(!list->head) return LIST_SUCCESS;
	if(!list->head->next) return LIST_SUCCESS;
	int to_iterator=1;
	if(list->iterator){
		Node ptr_find_iterator = list->head;
		while(ptr_find_iterator!=list->iterator){
			to_iterator++;
			ptr_find_iterator = ptr_find_iterator->next;
		}
	}
	Node ptr_i = list->head;
	while(ptr_i->next){
		Node ptr_j = ptr_i->next;
		while(ptr_j){
			if((compareElement(ptr_i->element, ptr_j->element, key))>0){
				ListElement temp = ptr_i->element;
				ptr_i->element = ptr_j->element;
				ptr_j->element = temp;
			}
			ptr_j = ptr_j->next;
		}
		ptr_i = ptr_i->next;
	}
	if(list->iterator){
		list->iterator = list->head;
		while(to_iterator>1){
			list->iterator = list->iterator->next;
			to_iterator--;
		}
	}
	return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
	if(!list || !filterElement) return NULL;
	Node dummy = createNode();
	if(!dummy) return NULL;
	Node previouse = dummy;
	Node ptr = list->head;
	while(ptr){
		if(filterElement(ptr->element, key)){
			Node new_node = createNode();
			if(!new_node) return NULL;
			new_node->element = list->copyElement(ptr->element);
			new_node->next = NULL;
			previouse->next = new_node;
			previouse = previouse->next;
		}
		ptr = ptr->next;
	}
	ptr = dummy->next;
	free(dummy);
	List new_list = listCreate(list->copyElement, list->freeElement);
	if(!new_list) return NULL;
	new_list->head = ptr;
	new_list->iterator = NULL;
	return new_list;
}

ListResult listClear(List list){
	if(!list) return LIST_NULL_ARGUMENT;
	Node ptr = list->head;
	while(ptr){
		list->head = list->head->next;
		list->freeElement(ptr->element);
		free(ptr);
		ptr = list->head;
	}
	list->iterator = NULL;
	return LIST_SUCCESS;
}

void listDestroy(List list){
	if(!list) return;
	listClear(list);
	free(list);
}
