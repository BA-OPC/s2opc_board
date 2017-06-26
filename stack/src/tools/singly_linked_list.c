/*
 *  Copyright (C) 2016 Systerel and others.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "singly_linked_list.h"

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct SLinkedList_Elt{
    uint32_t                id;
    void*                   value;
    struct SLinkedList_Elt* next;
};

struct SLinkedList {
    SLinkedList_Elt* first;
    SLinkedList_Elt* last;
    size_t           length;
    size_t           maxLength;
};

SLinkedList* SLinkedList_Create(size_t sizeMax){
    SLinkedList* result = malloc(sizeof(SLinkedList));
    if(result != NULL){
        memset(result, 0, sizeof(SLinkedList));
        result->maxLength = sizeMax;
    }
    return result;
}

void* SLinkedList_Prepend(SLinkedList* list, uint32_t id, void* value){
    SLinkedList_Elt* elt = NULL;
    if(list == NULL){
        return NULL;
    }

    if(list->length < list->maxLength || list->maxLength == 0){
        elt = malloc(sizeof(SLinkedList_Elt));
    }

    if(elt != NULL){
        elt->id = id;
        elt->value = value;
        elt->next = list->first;
        if(NULL == list->last){
            list->last = elt;
        }
        list->first = elt;
        list->length = list->length + 1;
    }else{
        return NULL;
    }

    return value;
}

void* SLinkedList_Append(SLinkedList* list, uint32_t id, void* value){
    SLinkedList_Elt* elt = NULL;
    if(list == NULL){
        return NULL;
    }

    if(list->length < list->maxLength || list->maxLength == 0){
        elt = malloc(sizeof(SLinkedList_Elt));
    }

    if(elt != NULL){
        elt->id = id;
        elt->value = value;
        elt->next = NULL;
        if(NULL == list->first){
            list->first = elt;
        }else{
            list->last->next = elt;
        }
        list->last = elt;
        list->length = list->length + 1;
    }else{
        return NULL;
    }

    return value;
}

void* SLinkedList_PopHead(SLinkedList* list){
    void* result = NULL;
    SLinkedList_Elt* nextElt = NULL;

    if(list == NULL || list->first == NULL){
       return NULL;
    }

    // First element is researched element
    list->length = list->length - 1;
    result = list->first->value;
    nextElt = list->first->next;
    free(list->first);
    list->first = nextElt;
    // If no element remaining, last element to be updated too
    if(NULL == list->first){
        list->last = NULL;
    }

    return result;
}

SLinkedList_Elt* SLinkedList_InternalFind(SLinkedList* list, uint32_t id){
    SLinkedList_Elt* elt = NULL;
    if(list != NULL){
        elt = list->first;
        while(elt != 0 && elt->id != id){
            elt = elt->next;
        }
    }
    return elt;
}

SLinkedList_Elt* SLinkedList_InternalFindPrec(SLinkedList* list, uint32_t id){
    SLinkedList_Elt* elt = NULL;
    if(list != NULL && list->first != NULL){
        elt = list->first;
        while(elt->next != NULL && elt->next->id != id){
            elt = elt->next;
        }
    }
    return elt;
}

// Returns null => Not found, otherwise => elt pointer
void* SLinkedList_FindFromId(SLinkedList* list, uint32_t id){
    SLinkedList_Elt* elt = SLinkedList_InternalFind(list, id);
    void* result = NULL;
    if(elt != NULL){
        result = elt->value;
    }
    return result;
}

void SLinkedList_Apply(SLinkedList* list, void (*pFn)(uint32_t id, void *val))
{
    SLinkedList_Elt* elt = NULL;

    if(NULL == list || NULL == pFn)
        return;

    elt = list->first;
    while(NULL != elt)
    {
        pFn(elt->id, elt->value);
        elt = elt->next;
    }
}

// Returns null => Not found, otherwise => elt pointer
void* SLinkedList_RemoveFromId(SLinkedList* list, uint32_t id){
    SLinkedList_Elt* elt = NULL;
    SLinkedList_Elt* nextElt = NULL;
    void* result = NULL;
    if(list != NULL && list->first != NULL){
        // Not NULL nor empty list
        if(list->first->id == id){
            // First element is researched element
            list->length = list->length - 1;
            result = list->first->value;
            nextElt = list->first->next;
            free(list->first);
            list->first = nextElt;
            // If no element remaining, last element to be updated too
            if(NULL == list->first){
                list->last = NULL;
            }
        }else{
            // Search element in rest of list
            elt = list->first;
            while(elt->next != NULL && elt->next->id != id){
                elt = elt->next;
            }
            if(elt->next != NULL){
                list->length = list->length - 1;
                result = elt->next->value;
                nextElt = elt->next->next;
                // If element is the last element, then set precedent element as precedent
                if(elt->next == list->last){
                    list->last = elt;
                }
                free(elt->next);
                elt->next = nextElt;
            }
        }
    }
    return result;
}

void SLinkedList_Clear(SLinkedList* list){
    SLinkedList_Elt* elt = NULL;
    SLinkedList_Elt* nextElt = NULL;
    if(list != NULL){
        elt = list->first;
        while(elt != NULL){
            nextElt = elt->next;
            free(elt);
            elt = nextElt;
        }
        list->first = NULL;
        list->last = NULL;
        list->length = 0;
    }
}

void SLinkedList_Delete(SLinkedList* list){
    if(list != NULL){
        SLinkedList_Clear(list);
        free(list);
    }
}


void SLinkedList_EltGenericFree(uint32_t id, void *val)
{
    (void)(id);
    free(val);
}

SLinkedListIterator SLinkedList_GetIterator(SLinkedList* list){
    return list->first;
}

void* SLinkedList_Next(SLinkedListIterator* it){
    SLinkedList_Elt* elt = NULL;
    void* value = NULL;
    if(it != NULL && *it != NULL){
        elt = *it;
        value = elt->value;
        *it = elt->next;
    }
    return value;
}
