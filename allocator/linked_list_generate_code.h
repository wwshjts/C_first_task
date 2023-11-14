#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>

#define LINKED_LIST_GENERATE_CODE(NAME, T)\
void NAME##_init(NAME * list){\
    list->head = NULL;\
    list->tail = NULL;\
    list->size = 0;\
}\
void NAME##_add_to_head(NAME * list, NAME##_node* v){\
    if (list->head){\
        v->next = list->head;\
        list->head->prev = v;\
        list->head = v;\
    }\
    else{\
        list->head = v;\
        list->tail = v;\
    }\
    list->size++;\
}\
void NAME##_add_to_tail(NAME * list, NAME##_node* v){\
    if(list->tail){\
        list->tail->next = v;\
        v->prev = list->tail;\
        list->tail = v;\
    }\
    else{\
        list->head = v;\
        list->tail = v;\
    }\
    list->size++;\
}\
void NAME##_free(NAME * list){\
    while(list->head){\
        NAME##_node* curr = list->head;\
        list->head = curr->next;\
        free(curr);\
    }\
    list->head = NULL;\
    list->tail = NULL;\
    list->size = 0;\
}\
int NAME##_is_empty(NAME * list){\
    return (list->head == NULL) && (list->tail == NULL);\
}\
NAME##_node* NAME##_pop_head(NAME * list){\
    NAME##_node * curr = list->head;\
    list->size--;\
    list->head = curr->next;\
    if(!list->head){\
        list->tail = NULL;\
    }\
    else list->head->prev = NULL;\
    return curr;\
}\
void NAME##_insert_prev(NAME * list, NAME##_node* curr, NAME##_node * node){\
    if(!curr->prev){\
        NAME##_add_to_head(list, node);\
    }\
    else{\
        list->size++;\
        node->next = curr;\
        node->prev = curr->prev;\
        curr->prev->next = node;\
        curr->prev = node;\
    }\
}\
void NAME##_delete(NAME * list, NAME##_node * node){\
    NAME##_node* prev = node->prev;\
    NAME##_node* next = node->next;\
    list->size--;\
    if(!prev && !next){\
        list->head = NULL;\
        list->tail = NULL;\
    }\
    if(prev && next){\
        next->prev = prev;\
        prev->next = next;\
    }\
    if(prev && !next){\
        prev->next = NULL;\
        list->tail = prev;\
    }\
    if(!prev && next){\
        next->prev = NULL;\
        list->head = next;\
    }\
}
