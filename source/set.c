#include <stddef.h>
#include <stdlib.h>

#include "set.h"
#include "list.h"


struct set{
    copySetElements copy;
    freeSetElements free;
    compareSetElements cmp;
    SetElement iterator;
    List setElements;
};






Set setCreate(copySetElements copyElement, freeSetElements freeElement,
	compareSetElements compareElements)
{
    if(copyElement == NULL || freeElement == NULL || compareElements == NULL) {return NULL;}
    Set new_set = (Set)malloc(sizeof(*new_set));
    if(!new_set) {return NULL;}
    new_set->copy = copyElement;
    new_set->free = freeElement;
    new_set->cmp = compareElements;
    new_set->iterator = NULL;
    new_set->setElements = listCreate(copyElement, freeElement);
    if(!new_set->setElements){
        free(new_set);
        return NULL;
    }
    return new_set;
}






void setDestroy(Set set){
    if(!set) {return;}
    set->iterator = NULL;
    listDestroy(set->setElements);
    free(set);
}






Set setCopy(Set set){
    if(set == NULL) {return NULL;}
    Set set_copy = setCreate(set->copy, set->free, set->cmp);
    if(!set_copy) {return NULL;}
    free(set_copy->setElements);
    set_copy->setElements = NULL;
    set_copy->setElements = listCopy(set->setElements);
    if(!set_copy->setElements){
        free(set_copy);
        return NULL;
    }
    return set_copy;
}





int setGetSize(Set set){
    if(set == NULL) {return -1;}
    return listGetSize(set->setElements);
}





bool setIsIn(Set set, SetElement element){
    if(set == NULL || element == NULL) return false;
    LIST_FOREACH(ListElement, curr, set->setElements){
        if(set->cmp((SetElement)curr, element) == 0) {return true;}
    }
    return false;
}





SetElement setGetFirst(Set set){
    if(set == NULL) {return NULL;}
    set->iterator = (SetElement)listGetFirst(set->setElements);
    if(set->iterator == NULL) {return NULL;}
    return set->iterator;
}





SetElement setGetNext(Set set){
    if(set == NULL) {return NULL;}
    set->iterator = (SetElement)listGetNext(set->setElements);
    if(set->iterator == NULL) {return NULL;}
    return set->iterator;
}








SetResult setAdd(Set set, SetElement element){
    if(set == NULL || element == NULL) {return SET_NULL_ARGUMENT;}
    if(setIsIn(set, element)) {return SET_ITEM_ALREADY_EXISTS;}
    if(LIST_SUCCESS != listInsertFirst(set->setElements, (ListElement)element)){
        return SET_OUT_OF_MEMORY;
    }
    return SET_SUCCESS;
}




SetResult setRemove(Set set, SetElement element){
    if(set == NULL || element == NULL) {return SET_NULL_ARGUMENT;}

    LIST_FOREACH(ListElement, curr, set->setElements){
        if(set->cmp((SetElement)curr,element) == 0){
            if(LIST_SUCCESS != listRemoveCurrent(set->setElements)){
                return SET_OUT_OF_MEMORY;
            }
            return SET_SUCCESS;
        }
    }
    return SET_ITEM_DOES_NOT_EXIST;
}





SetResult setClear(Set set){
    if(set == NULL) {return SET_NULL_ARGUMENT;}
    if(LIST_SUCCESS != listClear(set->setElements)){
        return SET_OUT_OF_MEMORY;
    }
    return SET_SUCCESS;
}